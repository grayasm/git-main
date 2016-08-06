   XStandardColormap \f(CWbest_map_info\fP;
   float red, green, blue;
   unsigned long pixelvalue;
   int status;

.XX "XGetStandardColormap, example using"
   status = XGetStandardColormap(display, RootWindow(display,
      screen), &best_map_info, XA_RGB_BEST_MAP);

   if (!status)
      {
      printf("%s: specified standard colormap not available", argv[0]);
      exit(-1);
      }

   pixelvalue = \f(CWbest_map_info\fP.base_pixel +
      ((unsigned long)(0.5 + (red * \f(CWbest_map_info\fP.red_max)) *
           \f(CWbest_map_info\fP.red_mult) + 
      ((unsigned long)(0.5 + (green * \f(CWbest_map_info\fP.green_max)) * 
           \f(CWbest_map_info\fP.green_mult) +
      ((unsigned long)(0.5 + (blue * \f(CWbest_map_info\fP.blue_max)) *
           \f(CWbest_map_info\fP.blue_mult);
