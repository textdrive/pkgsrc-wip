# $NetBSD: Makefile,v 1.15 2003/10/18 13:08:48 cjep Exp $
#

DISTNAME=	icecast-1.3.12
PKGREVISION=	3
CATEGORIES=	audio
MASTER_SITES=	http://www.icecast.org/files/

MAINTAINER=	hubertf@NetBSD.org
HOMEPAGE=	http://www.icecast.org/
COMMENT=	Internet broadcasting system using Mpeg Layer III streaming

PKG_DESTDIR_SUPPORT=	none

GNU_CONFIGURE=		yes

RCD_SCRIPTS=		icecast
PKG_SYSCONFSUBDIR=	icecast

.include "../../mk/bsd.prefs.mk"

CONFIGURE_ARGS+=	--with-readline \
			--with-libwrap

.if defined(ICECAST_USE_PYTHON) && ${ICECAST_USE_PYTHON} == YES
CONFIGURE_ARGS+=	--with-python
.include "../../lang/python/application.mk"
.endif

CPPFLAGS+=		-I${BUILDLINK_PREFIX.readline}/include/readline
CPPFLAGS+=		${BUILDLINK_CPPFLAGS.${PYPACKAGE}}
CFLAGS+=		${PTHREAD_CFLAGS}
LDFLAGS+=		${PTHREAD_LDFLAGS}
LDFLAGS+=		${BUILDLINK_LDFLAGS.${PYPACKAGE}}
LIBS+=			-lutil
PTHREAD_OPTS+=		require

EGDIR=			${PREFIX}/share/examples/icecast
EGFILES=		groups.aut mounts.aut users.aut icecast.conf

.for f in ${EGFILES}
CONF_FILES+=		${EGDIR}/${f}.dist ${PKG_SYSCONFDIR}/${f}
.endfor
.undef f

.include "../../devel/readline/buildlink3.mk"
.include "../../security/tcp_wrappers/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
