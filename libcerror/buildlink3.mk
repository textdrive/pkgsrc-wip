# $NetBSD$

BUILDLINK_TREE+=	libcerror

.if !defined(LIBCERROR_BUILDLINK3_MK)
LIBCERROR_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libcerror+=	libcerror>=20121222
BUILDLINK_PKGSRCDIR.libcerror?=	../../wip/libcerror

.endif	# LIBCERROR_BUILDLINK3_MK

BUILDLINK_TREE+=	-libcerror
