;; Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
;; <dimiro1@gmail.com>
;;
;; this is a simple major mode for working with twister assembler
;;
;; offerings:
;;
;; 1) syntax highlighting
;;
;; 2) simple indentation
;;
;; 3) a simple function for following branches. see the doc string
;; for twister-follow-branch. By default this is bound to "C-c C-j".
;;
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program. If not, see <http://www.gnu.org/licences>


(require 'regexp-opt)
(require 'cl)

(defvar twister-mode-syntax-table nil)

(defvar twister-label-regexp "[A-Za-z_][A-Za-z_0-9]*:")

(defvar twister-register "\\$[0-9]*")

(defvar twister-dotted-directives '(".main" ".end" ".options" ".name"))


(defvar twister-labeled-branching-ops '("goto" "lt_s" "gt_s" "lte_s"
													 "gte_s" "eq_s" "lt_n" "gt_n"
													 "lte_n" "gte_n" "eq_n" "not_lt_s"
													 "zero_n" "not_zero_n" "not_gt_s"
													 "not_lte_s" "not_gte_s" "not_eq_s"
													 "not_lt_n" "not_gt_n" "not_lte_n"
													 "not_gte_n" "not_eq_n")
  "All opcodes with jumps.")

(defvar twister-opcodes '("abs_n" "acos_n" "add_n" "asin_n"
								  "atan_n" "ceil_n" "cos_n" "dec_n"
								  "div_n" "floor_n" "inc_n" "log_n"
								  "mod_n" "mult_n" "neg_n" "pow_n"
								  "sin_n" "sqrt_n" "sub_n" "tan_n"
								  "input_n" "input_s" "halt" "nop"
								  "print_n" "print_s" "put_n" "put_s"
								  "mov_n" "mov_s" "store_s" "store_n"
								  "concat_s" "charat_s" "system_s"
								  "getenv_s" "rand_n")
  "All twister opcodes without jumps.")

(defvar twister-mode-map
  (let ((map (make-sparse-keymap)))
    (define-key map (kbd "RET") 'reindent-then-newline-and-indent)
    (define-key map (kbd "C-c C-j") 'twister-follow-branch)
    (define-key map (kbd "TAB") 'indent-according-to-mode)
	 map)
	 "Keymap for TWISTER major mode.")


(unless twister-mode-syntax-table
  (setq twister-mode-syntax-table (make-syntax-table))
  (modify-syntax-entry ?\\ "\\" twister-mode-syntax-table)
  (modify-syntax-entry ?#  "<"  twister-mode-syntax-table)
  (modify-syntax-entry ?\n ">"  twister-mode-syntax-table)
  (modify-syntax-entry ?:  "_"  twister-mode-syntax-table))

(setq twister-font-lock-keywords `(;; labels
											  (,(concat "^" twister-label-regexp) . font-lock-constant-face)
											  ;; twister registers
											  (,twister-register . font-lock-variable-name-face)
											  (,(regexp-opt twister-dotted-directives 'paren) . font-lock-keyword-face)
											  (,(regexp-opt twister-labeled-branching-ops 'paren) . font-lock-keyword-face)
											  ("mult_n" 0 font-lock-keyword-face t) ; A hack to match mult_n and highlighting
											  (,(regexp-opt twister-opcodes 'paren) . font-lock-keyword-face)))


(defun twister-mode ()
  "Simple Emacs mode for editing Twister Assembler"
  (interactive)
  (kill-all-local-variables)
  (setq major-mode 'twister-mode)
  (setq mode-name "TWISTER")
  (set-syntax-table twister-mode-syntax-table)
  (make-local-variable 'paragraph-start)
  (setq paragraph-start (concat "^$\\|" page-delimiter))
  (make-local-variable 'paragraph-separate)
  (setq paragraph-separate paragraph-start)
  (make-local-variable 'indent-line-function)
  (setq indent-line-function 'twister-indent-function)
  (make-local-variable 'require-final-newline)
  (setq require-final-newline t)
  (make-local-variable 'comment-start)
  (setq comment-start "# ")
  (make-local-variable 'comment-end)
  (setq comment-end "")
  (make-local-variable 'comment-start-skip)
  (setq comment-start-skip "#+ *")
  (make-local-variable 'comment-indent-function)
  (setq comment-indent-function 'twister-comment-indent)
  (make-local-variable 'font-lock-defaults)
  (setq font-lock-defaults '(twister-font-lock-keywords))
  (font-lock-mode 1)
  (use-local-map twister-mode-map)
  (run-hooks 'twister-mode-hook))

(defun twister-indent-line-function ()
  (interactive)
  (save-excursion
    (beginning-of-line)
    (delete-horizontal-space)
    (cond
     ((looking-at twister-label-regexp)
      (indent-to 0))
     ((looking-at (regexp-opt twister-dotted-directives))
      (indent-to 0))
     ((looking-at "^#")
      (indent-to 0))
     (t
		(indent-to 2)))))

(defun beginning-of-line-point (&optional n)
  "Return the point at the beginning of the current line. N gets
passed to beginning-of-line if you want"
  (save-excursion
    (beginning-of-line n)
    (point)))

(defun twister-indent-function ()
  "This differs from twister-indent-line-function in that if we end up at
the beginning of a line (which doesn't have a label) we want to be
moved forward to column 2"
  (interactive)
  (twister-indent-line-function)
  (unless (or (looking-at twister-label-regexp)
              (/= (beginning-of-line-point) (point)))
      (forward-char 2)))

(defun twister-comment-indent ()
  (interactive)
  (save-excursion
    (beginning-of-line)
    (delete-horizontal-space)
	 (indent-to 0)))

(defun twister-follow-branch ()
  "Look at the current op, it it's a branching op we jump to the
proper label (assuming it exists). In order to determine whether the
current op is branching or not we rely on the value of
*twister-labeled-branching-ops*"
  (interactive)
  (let ((jump-to-point nil))
    ;; jump-to-point and the save-excursion are so that if we're not
    ;; on a branching op line or if the op to jump to isn't defined we
    ;; don't move the point around unneccessarily (this would be very
    ;; confusing, trust me)
    (save-excursion
      (beginning-of-line)
      (save-match-data
        (when (looking-at (concat "^" twister-label-regexp))
          (search-forward ":")))
      (let ((op (buffer-substring (1- (search-forward-regexp "[^ \t\n\r]"))
                                  (1- (search-forward-regexp "[^a-zA-Z_]")))))
        (when (member op twister-labeled-branching-ops)
          ;; the label to jump to is the last sequence of [a-zA-Z_0-9]+
          ;; chars in this instruction
          (end-of-line)
          (search-backward-regexp "[^a-zA-Z_0-9]")
          (forward-char)
          (let ((label (buffer-substring (point) (1- (search-forward-regexp "[^a-zA-Z_0-9]")))))
            ;; label is the name (minus the traling ':') of the label
            ;; to jump to
            (beginning-of-buffer)
            (setq jump-to-point (search-forward (concat label ":")))))))
    (if jump-to-point
      (goto-char jump-to-point)
      (message "Not on branching op or undefined label"))))
