#ifndef PACKET_H
#define PACKET_H

#include <stdio.h>

#define BORN_BYTE      0x00
#define GREET_BYTE     0x10
#define GREET_ACK_BYTE 0x20
#define HEARTBEAT_BYTE 0x30
#define DEAD_BYTE      0x40

#define CLUSTER_TAG_LENGTH 2

typedef enum packet_types {
    BORN      = 0,
    GREET     = 1,
    GREET_ACK = 2,
    HEARTBEAT = 3,
    DEAD      = 4
} packet_types;

typedef enum encodings {
    UTF_8     = 0,
    UTF_16    = 1,
    ASCII     = 2,
    UNDEFINED = 3
} encodings;


/* HEADER */

typedef union header {
    unsigned char byte;
    struct {
        unsigned duplicate : 1; // Duplicated or not
        unsigned retain    : 1; // Store this packet
        unsigned encoding  : 2; // Encoding
        unsigned type      : 4; // Packet type
    } bits;
} disco_packet_header;

disco_packet_header packet_header(packet_types type, encodings encoding, short retain, short duplicate);


/* BORN Packet */

typedef struct born {
    disco_packet_header header;
    unsigned char cluster_tag[CLUSTER_TAG_LENGTH];
} disco_BORN;

disco_BORN born_packet(unsigned char cluster_tag[CLUSTER_TAG_LENGTH]);


/* GREET Packets */

typedef struct greet {
    disco_packet_header header;
} disco_GREET;

disco_GREET greet_packet(int duplicate);

typedef struct greet_ack {
    disco_packet_header header;
} disco_GREET_ACK;

disco_GREET_ACK greet_ack_packet(int duplicate);


/* HEARTBEAT Packet */

typedef struct hearbeat {
    disco_packet_header header;
} disco_HEARTBEAT;

disco_HEARTBEAT heartbeat_packet();


/* DEAD Packet */

typedef struct dead {
    disco_packet_header header;
    unsigned char cluster_tag[CLUSTER_TAG_LENGTH];
} disco_DEAD;

disco_DEAD dead_packet(unsigned char cluster_tag[CLUSTER_TAG_LENGTH]);


#endif