$NetBSD$

Install man pages under the right directory.
--- tools/install.py.orig	2012-12-12 22:44:54.000000000 +0000
+++ tools/install.py	2012-12-27 09:07:35.002233431 +0000
@@ -200,6 +200,8 @@
 
   if 'freebsd' in sys.platform:
     action(['doc/node.1'], 'man/man1/')
+  elif 'sunos' in sys.platform:
+    action(['doc/node.1'], 'man/man1/')
   else:
     action(['doc/node.1'], 'share/man/man1/')
 
