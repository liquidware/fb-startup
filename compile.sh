gcc -Wfatal-errors \
-mfpu=neon -mfloat-abi=softfp -mcpu=cortex-a8 -fomit-frame-pointer -O3 -fno-math-errno -fno-signed-zeros -fno-tree-vectorize \
-export-dynamic \
-I/usr/include/gtk-2.0 \
-I/usr/lib/gtk-2.0/include \
-I/usr/include/atk-1.0 \
-I/usr/include/cairo \
-I/usr/include/pango-1.0 \
-I/usr/include/glib-2.0 \
-I/usr/lib/glib-2.0/include \
-I/usr/include/freetype2 \
-I/usr/include/libpng12 \
-I/usr/include/libglade-2.0 \
-L/usr/lib \
-Xlinker -rpath -Xlinker /usr/lib \
-I. \
-lm -lpthread \
fb-startup.c \
-Xlinker -L/usr/lib -Xlinker -l:libgtk-x11-2.0.so.0 -l:libatk-1.0.so.0 \
-l:libgdk_pixbuf-2.0.so.0 -l:libpango-1.0.so.0 -l:libcairo.so.2 \
-l:libgobject-2.0.so.0 -l:libgmodule-2.0.so.0 -l:libdl.so \
-l:libglib-2.0.so.0 -l:libglade-2.0.so

#mkdir /usr/share/fb-startup
#cp a.out /usr/bin/fb-startup
#cp fb-startup.glade /usr/share/fb-startup/fb-startup.glade
#cp *.png /usr/share/fb-startup/



