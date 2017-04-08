(defun qmk-align-planck-layer (start end)
  "Align planck qmk layer."
  (interactive "r")
  (save-excursion
   (goto-char start)
   (while (re-search-forward " *, *" end t)
     (replace-match " , " t t))
   (goto-char start)
   (while (re-search-forward "{ *" end t)
     (replace-match "{ " t t))
   (goto-char start)
   (while (re-search-forward " *}" end t)
     (replace-match " }" t t))
   (align-regexp start end ",\\(\\s-*\\)" 1 1 t)))
