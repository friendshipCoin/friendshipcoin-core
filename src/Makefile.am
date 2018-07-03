DIST_SUBDIRS = secp256k1 leveldb

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

FRIENDSHIPCOIN_CONFIG_INCLUDES=-I$(builddir)/config
FRIENDSHIPCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)
FRIENDSHIPCOIN_INCLUDES += -I$(srcdir)/secp256k1/include

LIBFRIENDSHIPCOIN=libfriendshipcoin.a
LIBFRIENDSHIPCOIN_CLI=libfriendshipcoin_cli.a
LIBSECP256K1=secp256k1/libsecp256k1.la

secp256k1/libsecp256k1.la: $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

EXTRA_LIBRARIES += \
	$(LIBFRIENDSHIPCOIN) \
	$(LIBFRIENDSHIPCOIN_CLI)

if ENABLE_WALLET
FRIENDSHIPCOIN_INCLUDES += $(BDB_CPPFLAGS)
endif

bin_PROGRAMS = friendshipcoind

if BUILD_FRIENDSHIPCOIN_UTILS
  bin_PROGRAMS += friendshipcoin-cli
endif


.PHONY: FORCE
# friendshipcoin core #
FRIENDSHIPCOIN_CORE_H = activemasternode.h addrman.h alert.h allocators.h \
  base58.h bignum.h chainparamsbase.h chainparams.h chainparamsseeds.h checkpoints.h \
	clientversion.h coincontrol.h compat.h core.h crypter.h darksend-relay.h \
	darksend.h db.h ecwrapper.h hash.h hashblock.h init.h instantx.h kernel.h \
  key.h keystore.h limitedmap.h main.h miner.h mruset.h neoscrypt.h \
  net.h netbase.h noui.h pbkdf2.h pos.h protocol.h pubkey.h rpc/darksend.h \
	rpc/client.h rpc/protocol.h rpc/server.h script.h scrypt.h serialize.h \
	smessage.h spork.h stealth.h strlcpy.h sync.h threadsafety.h tinyformat.h \
	txdb-leveldb.h txdb.h txmempool.h ui_interface.h uint256.h util.h \
	version.h walletdb.h wallet.h

JSON_H = json/json_spirit.h json/json_spirit_error_position.h \
  json/json_spirit_reader.h json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h json/json_spirit_utils.h \
  json/json_spirit_value.h json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

CRYPTO_H = crypto/common.h crypto/hmac_sha256.h crypto/hmac_sha512.h \
	crypto/ripemd160.h crypto/sha1.h crypto/sha256.h crypto/sha512.h

SUPPORT_H = support/cleanse.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libfriendshipcoin_a-version.$(OBJEXT): obj/build.h

nodist_libfriendshipcoin_a_SOURCES = $(srcdir)/obj/build.h

libfriendshipcoin_a_CPPFLAGS = $(AM_CPPFLAGS) $(FRIENDSHIPCOIN_INCLUDES) \
															 $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) \
															 $(EVENT_PTHREADS_CFLAGS)
libfriendshipcoin_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

libfriendshipcoin_a_SOURCES = activemasternode.cpp addrman.cpp alert.cpp \
  allocators.cpp base58.cpp chainparamsbase.cpp chainparams.cpp \
	checkpoints.cpp core.cpp crypter.cpp crypto/hmac_sha256.cpp \
	crypto/hmac_sha512.cpp crypto/ripemd160.cpp crypto/sha1.cpp \
	crypto/sha256.cpp crypto/sha512.cpp db.cpp ecwrapper.cpp hash.cpp init.cpp \
	instantx.cpp kernel.cpp key.cpp keystore.cpp main.cpp \
  masternode.cpp masternodeconfig.cpp masternodeman.cpp  \
	masternode-payments.cpp miner.cpp neoscrypt.cpp net.cpp netbase.cpp \
	noui.cpp pbkdf2.cpp pos.cpp protocol.cpp pubkey.cpp rpc/blockchain.cpp \
	rpc/client.cpp rpc/darksend.cpp rpc/dump.cpp rpc/mining.cpp rpc/misc.cpp \
	rpc/net.cpp rpc/protocol.cpp rpc/rawtransaction.cpp rpc/server.cpp \
	rpc/smessage.cpp rpcwallet.cpp script.cpp scrypt.cpp smessage.cpp \
	spork.cpp stealth.cpp support/cleanse.cpp sync.cpp txdb-leveldb.cpp \
	txmempool.cpp util.cpp darksend.cpp darksend-relay.cpp version.cpp \
	wallet.cpp walletdb.cpp $(JSON_H) ($CRYPTO_H) $(FRIENDSHIPCOIN_CORE_H) \
	$(SUPPORT_H)

# cli: shared between friendshipcoin-cli and friendshipcoin-qt
libfriendshipcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(FRIENDSHIPCOIN_INCLUDES)
libfriendshipcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libfriendshipcoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(FRIENDSHIPCOIN_CORE_H)

# friendshipcoind binary #
friendshipcoind_SOURCES = friendshipcoind.cpp
friendshipcoind_CPPFLAGS = $(AM_CPPFLAGS) $(FRIENDSHIPCOIN_INCLUDES) \
													 $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) \
													 $(EVENT_PTHREADS_CFLAGS)
friendshipcoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
friendshipcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

friendshipcoind_LDADD = $(LIBFRIENDSHIPCOIN) $(LIBLEVELDB) $(LIBMEMENV) \
												$(LIBSECP256K1)
friendshipcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) \
												 $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS)

# friendshipcoin-cli binary #
friendshipcoin_cli_SOURCES = friendshipcoin-cli.cpp
friendshipcoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(FRIENDSHIPCOIN_INCLUDES) $(EVENT_CFLAGS) \
													 $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) \
													 $(EVENT_PTHREADS_CFLAGS)
friendshipcoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
friendshipcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

friendshipcoin_cli_LDADD = $(LIBFRIENDSHIPCOIN) $(LIBLEVELDB) $(LIBMEMENV) \
												$(LIBSECP256K1)
friendshipcoin_cli_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) \
												 $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS)

friendshipcoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(UNBOUND_LIBS) $(CURL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb secp256k1

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean 2>/dev/null
	rm -f leveldb/port/*.gcno leveldb/db/*.gcno leveldb/table/*.gcno leveldb/helpers/*.gcno
	rm -f leveldb/util/*.gcno leveldb/helpers/memenv/*.gcno

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif
