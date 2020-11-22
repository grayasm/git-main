; FindNext  handle  user_var(filename_output)
;
; Continues a search began with FindFirst.
; handle should be the handle_output_variable returned by FindFirst. 
; If the search is completed (there are no more files), filename_output is set
; to empty and the error flag is set. 
; Note that the filename output is without path.