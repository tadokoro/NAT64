#include "nat64/mod/rfc6052.h"
#include "nat64/comm/types.h"

#include <linux/module.h>
#include <linux/printk.h>


union ipv4_address {
	__be32 as32;
	__u8 as8[4];
};

int addr_6to4(struct in6_addr *src, struct ipv6_prefix *prefix, struct in_addr *dst)
{
	union ipv4_address dst_aux;

	switch (prefix->len) {
	case 32:
		dst_aux.as32 = src->s6_addr32[1];
		break;
	case 40:
		dst_aux.as8[0] = src->s6_addr[5];
		dst_aux.as8[1] = src->s6_addr[6];
		dst_aux.as8[2] = src->s6_addr[7];
		dst_aux.as8[3] = src->s6_addr[9];
		break;
	case 48:
		dst_aux.as8[0] = src->s6_addr[6];
		dst_aux.as8[1] = src->s6_addr[7];
		dst_aux.as8[2] = src->s6_addr[9];
		dst_aux.as8[3] = src->s6_addr[10];
		break;
	case 56:
		dst_aux.as8[0] = src->s6_addr[7];
		dst_aux.as8[1] = src->s6_addr[9];
		dst_aux.as8[2] = src->s6_addr[10];
		dst_aux.as8[3] = src->s6_addr[11];
		break;
	case 64:
		dst_aux.as8[0] = src->s6_addr[9];
		dst_aux.as8[1] = src->s6_addr[10];
		dst_aux.as8[2] = src->s6_addr[11];
		dst_aux.as8[3] = src->s6_addr[12];
		break;
	case 96:
		dst_aux.as32 = src->s6_addr32[3];
		break;
	default:
		log_err(ERR_PREF_LEN_RANGE, "Prefix has an invalid length: %u.", prefix->len);
		return -EINVAL;
	}

	dst->s_addr = dst_aux.as32;
	return 0;
}

int addr_4to6(struct in_addr *src, struct ipv6_prefix *prefix, struct in6_addr *dst)
{
	union ipv4_address src_aux;

	src_aux.as32 = src->s_addr;
	memset(dst, 0, sizeof(*dst));

	switch (prefix->len) {
	case 32:
		dst->s6_addr32[0] = prefix->address.s6_addr32[0];
		dst->s6_addr32[1] = src_aux.as32;
		break;
	case 40:
		dst->s6_addr32[0] = prefix->address.s6_addr32[0];
		dst->s6_addr[4] = prefix->address.s6_addr[4];
		dst->s6_addr[5] = src_aux.as8[0];
		dst->s6_addr[6] = src_aux.as8[1];
		dst->s6_addr[7] = src_aux.as8[2];
		dst->s6_addr[9] = src_aux.as8[3];
		break;
	case 48:
		dst->s6_addr32[0] = prefix->address.s6_addr32[0];
		dst->s6_addr[4] = prefix->address.s6_addr[4];
		dst->s6_addr[5] = prefix->address.s6_addr[5];
		dst->s6_addr[6] = src_aux.as8[0];
		dst->s6_addr[7] = src_aux.as8[1];
		dst->s6_addr[9] = src_aux.as8[2];
		dst->s6_addr[10] = src_aux.as8[3];
		break;
	case 56:
		dst->s6_addr32[0] = prefix->address.s6_addr32[0];
		dst->s6_addr[4] = prefix->address.s6_addr[4];
		dst->s6_addr[5] = prefix->address.s6_addr[5];
		dst->s6_addr[6] = prefix->address.s6_addr[6];
		dst->s6_addr[7] = src_aux.as8[0];
		dst->s6_addr[9] = src_aux.as8[1];
		dst->s6_addr[10] = src_aux.as8[2];
		dst->s6_addr[11] = src_aux.as8[3];
		break;
	case 64:
		dst->s6_addr32[0] = prefix->address.s6_addr32[0];
		dst->s6_addr32[1] = prefix->address.s6_addr32[1];
		dst->s6_addr[9] = src_aux.as8[0];
		dst->s6_addr[10] = src_aux.as8[1];
		dst->s6_addr[11] = src_aux.as8[2];
		dst->s6_addr[12] = src_aux.as8[3];
		break;
	case 96:
		dst->s6_addr32[0] = prefix->address.s6_addr32[0];
		dst->s6_addr32[1] = prefix->address.s6_addr32[1];
		dst->s6_addr32[2] = prefix->address.s6_addr32[2];
		dst->s6_addr32[3] = src_aux.as32;
		break;
	default:
		log_err(ERR_PREF_LEN_RANGE, "Prefix has an invalid length: %u.", prefix->len);
		return -EINVAL;
	}

	return 0;
}
