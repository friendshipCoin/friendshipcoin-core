DIST_SUBDIRS = secp256k1 leveldb

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

FRIENDSHIPCOIN_CONFIG_INCLUDES=-I$(builddir)/config
FRIENDSHIPCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)
FRIENDSHIPCOIN_INCLUDES += -I$(srcdir)/secp256k1/include

LIBFRIENDSHIPCOIN=libfriendshipcoin.a
LIBSECP256K1=secp256k1/libsecp256k1.la

secp256k1/libsecp256k1.la: $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

EXTRA_LIBRARIES += libfriendshipcoin.a

if ENABLE_WALLET
FRIENDSHIPCOIN_INCLUDES += $(BDB_CPPFLAGS)
endif

bin_PROGRAMS = friendshipcoind

.PHONY: FORCE
# friendshipcoin core #
FRIENDSHIPCOIN_CORE_H = activemasternode.h addrman.h alert.h allocators.h \
  base58.h bignum.h chainparams.h chainparamsseeds.h checkpoints.h \
	clientversion.h coincontrol.h compat.h core.h crypter.h darksend-relay.h \
	darksend.h db.h ecwrapper.h hash.h hashblock.h init.h instantx.h kernel.h \
  key.h keystore.h limitedmap.h main.h miner.h mruset.h neoscrypt.h \
  net.h netbase.h noui.h pbkdf2.h pos.h protocol.h pubkey.h rpcdarksend.h \
	rpcclient.h rpcprotocol.h rpcserver.h script.h scrypt.h serialize.h \
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
libfriendshipcoin_a-clientversion.$(OBJEXT): obj/build.h

nodist_libfriendshipcoin_a_SOURCES = $(srcdir)/obj/build.h

libfriendshipcoin_a_CPPFLAGS = $(AM_CPPFLAGS) $(FRIENDSHIPCOIN_INCLUDES) \
															 $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) \
															 $(EVENT_PTHREADS_CFLAGS)
libfriendshipcoin_a_CXXFLAGS = $(AM_CXXFLAGS)

libfriendshipcoin_a_SOURCES = activemasternode.cpp addrman.cpp alert.cpp \
  allocators.cpp base58.cpp chainparams.cpp checkpoints.cpp \
  core.cpp crypter.cpp crypto/hmac_sha256.cpp crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp crypto/sha1.cpp crypto/sha256.cpp crypto/sha512.cpp \
  db.cpp ecwrapper.cpp hash.cpp init.cpp \
	instantx.cpp kernel.cpp key.cpp keystore.cpp main.cpp \
  masternode.cpp masternodeconfig.cpp masternodeman.cpp  \
	masternode-payments.cpp miner.cpp neoscrypt.c net.cpp netbase.cpp noui.cpp \
  pbkdf2.cpp pos.cpp protocol.cpp pubkey.cpp rpcblockchain.cpp rpcclient.cpp \
	rpcdarksend.cpp rpcdump.cpp rpcmining.cpp rpcmisc.cpp rpcnet.cpp \
	rpcprotocol.cpp rpcrawtransaction.cpp rpcserver.cpp rpcsmessage.cpp \
	rpcwallet.cpp script.cpp scrypt.cpp smessage.cpp spork.cpp stealth.cpp \
  support/cleanse.cpp sync.cpp txdb-leveldb.cpp txmempool.cpp util.cpp \
	darksend.cpp darksend-relay.cpp version.cpp wallet.cpp walletdb.cpp \
	$(JSON_H) ($CRYPTO_H) $(FRIENDSHIPCOIN_CORE_H) $(SUPPORT_H)



# friendshipcoind binary #
friendshipcoind_SOURCES = bitcoind.cpp
friendshipcoind_CPPFLAGS = $(AM_CPPFLAGS) $(FRIENDSHIPCOIN_INCLUDES) \
													 $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) \
													 $(EVENT_PTHREADS_CFLAGS)
friendshipcoind_CXXFLAGS = $(AM_CXXFLAGS)
friendshipcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

friendshipcoind_LDADD = $(LIBFRIENDSHIPCOIN) $(LIBLEVELDB) $(LIBMEMENV) \
												$(LIBSECP256K1)
friendshipcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) \
												 $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS)

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
