#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "config.h"
#include "compat.h"
#include "net.h"
#include "random.h"

void nfc_gen_sockaddr(unsigned long *addr, unsigned long *addrlen)
{
	struct sockaddr_nfc *nfc;

	// TODO: See also sockaddr_nfc_llcp
	nfc = malloc(sizeof(struct sockaddr_nfc));
	if (nfc == NULL)
		return;

	nfc->sa_family = PF_NFC;
	nfc->dev_idx = rand();
	nfc->target_idx = rand();
	nfc->nfc_protocol = rand() % 5;
	*addr = (unsigned long) nfc;
	*addrlen = sizeof(struct sockaddr_nfc);
}

void nfc_rand_socket(struct proto_type *pt)
{
	if (rand_bool()) {
		pt->protocol = NFC_SOCKPROTO_LLCP;
		if (rand_bool())
			pt->type = SOCK_DGRAM;
		else
			pt->type = SOCK_STREAM;
		return;
	}

	pt->protocol = NFC_SOCKPROTO_RAW;
	pt->type = SOCK_SEQPACKET;
}
