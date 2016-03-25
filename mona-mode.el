;;; mona-mode.el -- Emacs MONA mode

;; Copyright (C) 1997-2016 Aarhus University.
;; 
;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to the  Free Software
;; Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA 02110-1335,
;; USA.

;; Usage:
;; Insert the following into your .emacs file:
;;
;;   (load "<directory>/mona-mode")
;;   (global-font-lock-mode t)
;;
;; where <directory> is the name of the directory containing this file.
;; If font-lock is already enabled you don't need to insert the second line.

(require 'font-lock)

(defvar mona-mode-font-lock-keywords
  `(
    (,(regexp-opt
       '("all0" "all1" "all2" "ex0" "ex1" "ex2" "true" "false"
	 "let0" "let1""let2" "pred" "macro" "assert" "inter" "sub"
	 "union" "in" "notin" "var0" "var1" "var2" "linear" "tree"
	 "universe" "root" "guide" "const" "defaultwhere1"
	 "defaultwhere2" "empty" "m2l-str" "m2l-tree" "lastpos"
	 "where" "max" "min" "include" "export" "prefix" "execute"
	 "ws1s" "ws2s" "import" "in_state_space" "variant" "verify"
	 "succ" "tree" "tree_root" "type" "const_tree"
	 "well_formed_tree" "allpos" "sometype" "restrict")
       'words) . font-lock-keyword-face))
  "Regular expression to match Mona keywords")

(defvar mona-mode-syntax-table 
  (let ((table (make-syntax-table)))
    (modify-syntax-entry ?/ ". 14" table)
    (modify-syntax-entry ?* ". 23" table)
    (modify-syntax-entry ?# "<" table)
    (modify-syntax-entry ?\n ">" table)
    (modify-syntax-entry ?\f ">" table)
    (modify-syntax-entry ?' "w" table)
    (modify-syntax-entry ?_ "w" table)
    (modify-syntax-entry ?@ "w" table)
    (modify-syntax-entry ?$ "w" table)
    table)
  "Syntax table in use in mona-mode buffers.")

(if (featurep 'xemacs)
    (put 'mona-mode 'font-lock-defaults
	 '(mona-mode-font-lock-keywords
	   nil nil nil backward-paragraph)))

(defun mona-mode ()
  "Major mode for editing MONA files"

  (interactive)

  (kill-all-local-variables)

  (setq mode-name "MONA")
  (setq major-mode 'mona-mode)
  (set-syntax-table mona-mode-syntax-table)
  (if (not (featurep 'xemacs))
      (setq font-lock-defaults
	    '(mona-mode-font-lock-keywords
	      nil nil nil backward-paragraph)))
  (run-hooks 'mona-mode-hook))

(or (assoc "\\.mona$" auto-mode-alist)
    (setq auto-mode-alist (cons '("\\.mona$" . mona-mode)
				auto-mode-alist)))

(provide 'mona-mode)
