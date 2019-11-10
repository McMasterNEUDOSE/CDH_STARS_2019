# LibCSP Make Module

# LibCSP Path
LIBCSP_DIR = ext/libcsp

# Includes
INCLUDES += -I$(LIBCSP_DIR)/include  \
			-I$(LIBCSP_DIR)/src

# CAN include
INCLUDES +=	-I$(LIBCSP_DIR)/src/interfaces/can

# LibCSP FreeRTOS sources
SOURCES += 	$(LIBCSP_DIR)/src/arch/freertos/csp_malloc.c		\
		   	$(LIBCSP_DIR)/src/arch/freertos/csp_queue.c		\
		   	$(LIBCSP_DIR)/src/arch/freertos/csp_semaphore.c	\
		   	$(LIBCSP_DIR)/src/arch/freertos/csp_system.c		\
		   	$(LIBCSP_DIR)/src/arch/freertos/csp_thread.c		\
		   	$(LIBCSP_DIR)/src/arch/freertos/csp_time.c

# Interfaces (Loopback + CAN)
SOURCES += 	$(LIBCSP_DIR)/src/interfaces/csp_if_lo.c	\
		   	$(LIBCSP_DIR)/src/interfaces/csp_if_can.c	\
			$(LIBCSP_DIR)/src/interfaces/csp_if_can_pbuf.c

# RTable
SOURCES += 	$(LIBCSP_DIR)/src/rtable/csp_rtable_static.c

# Transport
SOURCES += 	$(LIBCSP_DIR)/src/transport/csp_udp.c

# Source files
SOURCES += 	$(LIBCSP_DIR)/src/csp_bridge.c     		\
		   	$(LIBCSP_DIR)/src/csp_buffer.c     		\
			$(LIBCSP_DIR)/src/csp_conn.c       		\
			$(LIBCSP_DIR)/src/csp_crc32.c     		\
			$(LIBCSP_DIR)/src/csp_debug.c      		\
			$(LIBCSP_DIR)/src/csp_dedup.c      		\
			$(LIBCSP_DIR)/src/csp_endian.c     		\
			$(LIBCSP_DIR)/src/csp_iflist.c     		\
			$(LIBCSP_DIR)/src/csp_io.c 				\
			$(LIBCSP_DIR)/src/csp_init.c 				\
			$(LIBCSP_DIR)/src/csp_port.c       		\
			$(LIBCSP_DIR)/src/csp_promisc.c    		\
			$(LIBCSP_DIR)/src/csp_qfifo.c      		\
			$(LIBCSP_DIR)/src/csp_route.c     		\
			$(LIBCSP_DIR)/src/csp_services.c   		\
			$(LIBCSP_DIR)/src/csp_service_handler.c   	\
			$(LIBCSP_DIR)/src/csp_sfp.c


