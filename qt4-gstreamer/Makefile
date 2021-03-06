# $NetBSD$
#

DISTNAME=	qt-gstreamer-0.10.2
PKGNAME=	${DISTNAME:S/qt/qt4/1}
CATEGORIES=	multimedia x11
MASTER_SITES=	http://gstreamer.freedesktop.org/data/src/qt-gstreamer/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://gstreamer.freedesktop.org/data/src/qt-gstreamer/
COMMENT=	C++ bindings (libraries and plugins) for GStreamer with a Qt-style API
LICENSE=	gnu-lgpl-v2.1

WRKSRC=		${WRKDIR}/${DISTNAME}
USE_TOOLS+=	gmake pkg-config
USE_CMAKE=	yes
USE_LANGUAGES=	c c++
GCC_REQD=	4.5

PKGCONFIG_OVERRIDE+=	src/QGlib/QtGLib-2.0.pc.in
PKGCONFIG_OVERRIDE+=	src/QGst/QtGStreamer-0.10.pc.in
PKGCONFIG_OVERRIDE+=	src/QGst/QtGStreamerUtils-0.10.pc.in
PKGCONFIG_OVERRIDE+=	src/QGst/QtGStreamerUi-0.10.pc.in

.include "options.mk"

CMAKE_ARGS+=		-DQTGSTREAMER_EXAMPLES=ON -DUSE_GST_PLUGIN_DIR=ON
CMAKE_ARGS+=		-DQTGSTREAMER_CODEGEN=OFF # XXX breaks cross-compile
CMAKE_ARGS+=		-DUSE_QT_PLUGIN_DIR=OFF
CXXFLAGS+=		-std=c++0x

BUILDLINK_API_DEPENDS.boost-headers+=	boost-headers>=1.39
.include "../../devel/boost-headers/buildlink3.mk"
BUILDLINK_API_DEPENDS.qt4-libs+=	qt4-libs>=4.7
.include "../../x11/qt4-libs/buildlink3.mk"
.include "../../multimedia/gst-plugins0.10-base/buildlink3.mk"
.include "../../multimedia/gstreamer0.10/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../graphics/MesaLib/buildlink3.mk"
.include "../../x11/libICE/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libX11/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
