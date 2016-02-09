Chapter 6 Using GLib

Basic Data Types
      gboolean          : TRUE or FALSE, no equivalent in C
      gchar (guchar)    : signed and unsigned C character type
      gconstpointer     : pointer to constant data that is untyped.
      gdouble           : C double type
      gfloat            : C float type
      gint (guint)      : signed, unsigned C int type
      gint8 (guint8)    : 8 bits on all platforms, signed and unsigned
      gint16 (guint16)  : 16 bits on all platforms, signed and unsigned
      gint32 (guint32)  : 32 bits on all platforms, signed and unsigned
      gint64 (guint64)  : 64 bits on all platforms, signed and unsigned
      glong (gulong)    : signed, unsigned C long type
      gpointer          : untype pointer defined a C void*
      gshort (gushort)  : signed, unsigned C short
      gsize (gssize)    : signed, unsigned 32 bit integers

Standard Macros:
/usr/include/glib-2.0/glib/gversion.h
      GLIB_MAJOR_VERSION        : major version of GLib headers
      GLIB_MINOR_VERSION        : minor ...
      GLIB_MICRO_VERSION        : micro ...
      GLIB_CHECK_VERSION
      (major, minor, micro)     : macro to check the current GLib version
      ABS (a)                   : absolute value of a
      CLAMP (a, low, high)      : returns a or range boundaries when outside
      G_DIR_SEPARATOR           : platform path separator as a char
      G_DIR_SEPARATOR_S         : platform path separator as a string
      GINT_TO_POINTER (i)       : converts gint to gpointer
      GPOINTER_TO_INT (p)       :          gpointer to int
      GSIZE_TO_POINTER (s)      :          gsize to gpointer
      GPOINTER_TO_SIZE (p)      :          gpointer to gsize
      GUINT_TO_POINTER (u)      :          guint to gpointer
      GPOINTER_TO_UINT (p)      :          gpointer to gint
      G_OS_WIN32                : define code that will be run on specific OS
      G_OS_BEOS
      G_OS_UNIX
      G_STRUCT_MEMBER
      (type, struct_p, offset)  : returns structure's member at offset
      G_STRUCT_MEMBER_P
      (struct_p, offset)        : return pointer to structure's member at offset
      G_STRUCT_OFFSET
      (type, member)            : return the byte offset to member of structure
      MIN (a,b)                 : min
      MAX (a,b)
      TRUE,FALSE                : 0, !0

/usr/include/glib-2.0/glib/gtypes.h
      G_E                       : base of ln with 49 decimal places (e)
      G_LN2                     : ln(2) with 50 decimal places
      G_LN10                    : ln(1) with 49 decimal places
      G_PI                      : pi with 49 decimal places

/usr/include/glib-2.0/glib/gmessages.h
      G_LOG_LEVEL_ERROR         : error that is always fatal, exits application

/usr/include/glib-2.0/glib/glice.h
      gpointer g_slice_alloc (gsize block_size);
      void     g_slice_free1 (gsize block_size, gpointer mem_block);
                                : allocate memory in blocks using either
                                  a) the SLAB allocator or
                                  b) g_malloc
                                  objects must not need be resized later :)
                                  objects must be the same size when it was
                                  allocated and when it was freed.

/usr/include/glib-2.0/glib/gprintf.h
        gint g_printf(gchar const *format, ...);

/usr/include/glib-2.0/glib/gmem.h
        #define g_new(struct_type, n_structs)
        void g_free (gpointer mem);

        to profile memory usage:
        g_mem_set_v_table + g_mem_profile (see sample memprofile.c)


Utility functions:
/usr/include/glib-2.0/glib/gutils.h
        g_get_current_dir ()
        g_get_home_dir ()
        g_get_host_name ()
        g_get_real_name ()
        g_get_tmp_dir ()
        g_get_user_name (), etc.

Timer functions:
/usr/include/glib-2.0/glib/gtimer.h
