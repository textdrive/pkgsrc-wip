# $NetBSD$
#

DISTNAME=		snes9express-1.42
PKGREVISION=		1
CATEGORIES=		emulators x11
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=snes9express/}

MAINTAINER=		ccatrian@eml.cc
HOMEPAGE=		http://www.linuxgames.com/snes9express/
COMMENT=		Frontend for snes9x written in GTK2

DEPENDS+=		snes9x>=1.39:../../emulators/snes9x

PKG_DESTDIR_SUPPORT=	none

GNU_CONFIGURE=		yes
USE_LANGUAGES=		c c++
USE_TOOLS+=		autoconf pkg-config

.include "../../x11/gtk2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
