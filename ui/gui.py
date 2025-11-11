import os
import sys
import subprocess
import tkinter as tk
from tkinter import ttk, filedialog, messagebox, scrolledtext
import datetime
import re

APP_TITLE = "DikLang Compiler UI"
TABS = ["Tokens", "Parser", "Semantic", "IR", "Optimized", "Emitted", "Errors", "Full Log"]

def find_compiler():
    """
    Resolve path to compiler.exe assuming this UI lives in CustomCompiler/ui/gui.py
    """
    here = os.path.abspath(os.path.dirname(__file__))
    root = os.path.abspath(os.path.join(here, ".."))
    exe = "compiler.exe" if os.name == "nt" else "compiler"
    path = os.path.join(root, exe)
    return path, root

def parse_output(stdout: str, stderr: str):
    """
    Split compiler output into sections for tabs.
    We detect sections by the headings your compiler already prints.
    Robust to minor message changes.
    """
    sections = {k: [] for k in TABS}

    lines = stdout.splitlines()
    current = "Full Log"
    for raw in lines:
        line = raw.rstrip()
        sections["Full Log"].append(line)

        
        if re.search(r"^TOKENS GENERATED", line):
            current = "Tokens";  continue
        if re.search(r"^Generated Intermediate Code|^Generating Intermediate Code", line):
            current = "IR";      continue
        if re.search(r"^Final Optimized Intermediate Code|^Optimized Intermediate Code|^Optimization completed", line):

            if "Final Optimized" in line:
                current = "Optimized"
            continue
        if re.search(r"^Emitted Target-like Code", line):
            current = "Emitted"; continue
        if re.search(r"Parsing", line):
            sections["Parser"].append(line);  continue
        if re.search(r"Semantic", line):
            sections["Semantic"].append(line); continue


        if line.strip().startswith("<") and line.strip().endswith(">"):
            sections["Tokens"].append(line)
            continue


        if current in ("IR", "Optimized", "Emitted"):
            if line.strip() and not line.endswith(":"):
                sections[current].append(line)
            continue


    for src in (stdout, stderr):
        for errline in src.splitlines():
            if any(key in errline for key in ("[Syntax Error]", "[Semantic Error]", "Error:", "fatal", "undefined")):
                sections["Errors"].append(errline)

    return {k: "\n".join(v).strip() for k, v in sections.items()}

class CompilerUI(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title(APP_TITLE)
        self.geometry("980x650")
        self.minsize(900, 560)


        self.compiler_path, self.project_root = find_compiler()


        top = ttk.Frame(self, padding=(8, 8))
        top.pack(fill=tk.X)

        self.path_var = tk.StringVar()
        self.path_entry = ttk.Entry(top, textvariable=self.path_var)
        self.path_entry.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=(0,8))

        ttk.Button(top, text="Browse", command=self.on_browse).pack(side=tk.LEFT)
        ttk.Button(top, text="Compile", style="Accent.TButton", command=self.on_compile).pack(side=tk.LEFT, padx=8)
        ttk.Button(top, text="Save Log", command=self.on_save_log).pack(side=tk.LEFT)


        self.nb = ttk.Notebook(self)
        self.nb.pack(fill=tk.BOTH, expand=True, padx=8, pady=8)

        self.text_widgets = {}
        for name in TABS:
            frame = ttk.Frame(self.nb)
            self.nb.add(frame, text=name)
            txt = scrolledtext.ScrolledText(frame, wrap=tk.WORD, font=("Consolas", 10))
            txt.pack(fill=tk.BOTH, expand=True)
            self.text_widgets[name] = txt

 
        self.status = tk.StringVar(value=f"Compiler: {self.compiler_path}")
        ttk.Label(self, textvariable=self.status, anchor="w", padding=(8,4)).pack(fill=tk.X, side=tk.BOTTOM)


        style = ttk.Style()
        try:
            style.theme_use("clam")
        except:
            pass
        style.configure("Accent.TButton", font=("Segoe UI", 10, "bold"))

    def on_browse(self):
        fp = filedialog.askopenfilename(
            initialdir=os.path.join(self.project_root, "test"),
            title="Select a DikLang source file",
            filetypes=[("DikLang files", "*.dik"), ("All files", "*.*")]
        )
        if fp:
            self.path_var.set(fp)

    def on_compile(self):
        src = self.path_var.get().strip()
        if not src:
            messagebox.showwarning("Pick a file", "Please choose a .dik file to compile.")
            return
        if not os.path.exists(self.compiler_path):
            messagebox.showerror("Compiler not found", f"Could not find {self.compiler_path}\nBuild the project first.")
            return
        if not os.path.isfile(src):
            messagebox.showerror("File missing", f"Cannot find:\n{src}")
            return

       
        for t in TABS:
            self.text_widgets[t].delete("1.0", tk.END)

        self.status.set("Compiling…")

        
        try:
            result = subprocess.run(
                [self.compiler_path, src],
                cwd=self.project_root,
                capture_output=True,
                text=True
            )
        except Exception as e:
            messagebox.showerror("Run failed", str(e))
            self.status.set("Run failed")
            return

        sections = parse_output(result.stdout, result.stderr)

        # Fill tabs
        for name, text in sections.items():
            self.text_widgets[name].insert(tk.END, text or "(no output)")


        if sections["Errors"]:
            self.nb.select(self.nb.tabs()[TABS.index("Errors")])
            self.status.set("Completed with errors • " + datetime.datetime.now().strftime("%H:%M:%S"))
        else:
            pref = "Optimized" if sections["Optimized"] else ("IR" if sections["IR"] else "Tokens")
            self.nb.select(self.nb.tabs()[TABS.index(pref)])
            self.status.set("Compilation successful • " + datetime.datetime.now().strftime("%H:%M:%S"))

    def on_save_log(self):
        save_path = filedialog.asksaveasfilename(
            defaultextension=".txt",
            filetypes=[("Text file", "*.txt")],
            initialfile="compiler_output.txt",
            title="Save combined output"
        )
        if not save_path:
            return
        try:
            with open(save_path, "w", encoding="utf-8") as f:
                for tab in TABS:
                    f.write(f"===== {tab} =====\n")
                    f.write(self.text_widgets[tab].get("1.0", tk.END).strip())
                    f.write("\n\n")
            messagebox.showinfo("Saved", f"Output saved to:\n{save_path}")
        except Exception as e:
            messagebox.showerror("Save failed", str(e))

if __name__ == "__main__":
    app = CompilerUI()
    app.mainloop()
