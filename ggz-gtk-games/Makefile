# $NetBSD$
#

DISTNAME=	ggz-gtk-games-0.0.14
PKGREVISION=	1
CATEGORIES=	games
MASTER_SITES=	http://mirrors.ibiblio.org/pub/mirrors/ggzgamingzone/ggz/0.0.14/

MAINTAINER=	mrohrer@users.sourceforge.net
HOMEPAGE=	http://www.ggzgamingzone.org
COMMENT=	GGZ Gaming Zone libraries

PKG_DESTDIR_SUPPORT=	none

CONFIGURE_ARGS+= --enable-debug-gdb

GNU_CONFIGURE=	yes

.include "../../x11/gtk2/buildlink3.mk"
.include "../../games/ggz-client-libs/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
