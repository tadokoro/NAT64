#ifndef _NF_NAT64_FILTERING_H
#define _NF_NAT64_FILTERING_H

/**
 * @file
 * Second step of the stateful NAT64 translation algorithm: "Filtering and Updating Binding and
 * Session Information", as defined in RFC6146 section 3.5.
 *
 * @author Roberto Aceves
 * @author Alberto Leiva
 */

#include "nat64/comm/types.h"
#include "nat64/comm/config_proto.h"
#include "nat64/mod/packet.h"


int filtering_init(void);
void filtering_destroy(void);

int clone_filtering_config(struct filtering_config *clone);
int set_filtering_config(__u32 operation, struct filtering_config *new_config);

verdict filtering_and_updating(struct fragment *frag, struct tuple *tuple);


#endif /* _NF_NAT64_FILTERING_H */
