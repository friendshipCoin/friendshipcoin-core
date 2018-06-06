AM_CPPFLAGS =  $(INCLUDES) -I$(top_builddir)/src/obj \
  -I$(top_srcdir)/src/leveldb/include -I$(top_srcdir)/src/leveldb/helpers \
  $(BOOST_INCLUDES)
AM_LDFLAGS = $(PTHREAD_CFLAGS)

secp256k1/libsecp256k1.la: $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	@$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

noinst_LIBRARIES = libfriendshipcoin.a

bin_PROGRAMS = friendshipcoind

AM_CPPFLAGS += -I$(top_srcdir)/src/secp256k1/include
AM_CPPFLAGS += -std=c++11

LIBPATHS= \
 -L"$(CURDIR)/secp256k1/src/.libs"

SUBDIRS = .
DIST_SUBDIRS = .
.PHONY: FORCE
# friendshipcoin core #
FRIENDSHIPCOIN_CORE_H = activemasternode.h addrman.h alert.h allocators.h \
  base58.h bignum.h chainparams.h chainparamsseeds.h checkpoints.h \
	clientversion.h coincontrol.h compat.h core.h crypter.h darksend-relay.h \
	darksend.h db.h ecwrapper.h hash.h hashblock.h init.h instantx.h kernel.h \
  key.h keystore.h limitedmap.h main.h miner.h mruset.h neoscrypt.h \
  net.h netbase.h pbkdf2.h pos.h protocol.h pubkey.h rpcclient.h rpcprotocol.h \
	rpcserver.h script.h scrypt.h serialize.h smessage.h spork.h stealth.h \
	strlcpy.h sync.h threadsafety.h tinyformat.h txdb-leveldb.h txdb.h \
  txmempool.h ui_interface.h uint256.h util.h utilstrencodings.h \
	version.h walletdb.h wallet.h

JSON_H = json/json_spirit.h json/json_spirit_error_position.h \
  json/json_spirit_reader.h json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h json/json_spirit_utils.h \
  json/json_spirit_value.h json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(abs_top_builddir)/src/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
version.o: obj/build.h

libfriendshipcoin_a_SOURCES = activemasternode.cpp addrman.cpp alert.cpp \
	allocators.cpp base58.cpp chainparams.cpp checkpoints.cpp \
	core.cpp crypter.cpp darksend-relay.cpp darksend.cpp db.cpp ecwrapper.cpp \
	hash.cpp init.cpp instantx.cpp kernel.cpp key.cpp keystore.cpp main.cpp \
	masternode-payments.cpp masternode.cpp masternodeconfig.cpp \
	masternodeman.cpp miner.cpp neoscrypt.c net.cpp netbase.cpp noui.cpp \
	pbkdf2.cpp pos.cpp protocol.cpp pubkey.cpp rpcblockchain.cpp rpcclient.cpp \
	rpcdump.cpp rpcmining.cpp rpcmisc.cpp rpcnet.cpp rpcprotocol.cpp \
	rpcrawtransaction.cpp rpcserver.cpp rpcsmessage.cpp rpcwallet.cpp \
	script.cpp scrypt.cpp smessage.cpp spork.cpp stealth.cpp sync.cpp \
	txdb-leveldb.cpp txmempool.cpp util.cpp utilstrencodings.cpp \
	version.cpp wallet.cpp walletdb.cpp $(JSON_H) \
  $(FRIENDSHIPCOIN_CORE_H)

nodist_libfriendshipcoin_a_CPPFLAGS = $(FRIENDSHIPCOIN_INCLUDES)
nodist_libfriendshipcoin_a_SOURCES = $(top_srcdir)/src/obj/build.h
#

# friendshipcoind binary #
friendshipcoind_LDADD = libfriendshipcoin.a leveldb/libleveldb.a leveldb/libmemenv.a \
  $(BOOST_LIBS) $(LIBPATHS)
friendshipcoind_SOURCES = bitcoind.cpp
#

leveldb/libleveldb.a:
	@echo "Building LevelDB ..." && cd leveldb && CXX="$(CXX)" CC="$(CC)" \
	  PLATFORM=$(TARGET_OS) AR="$(AR)" $(MAKE) $(LEVELDB_TARGET_FLAGS) OPT="$(CXXFLAGS) $(CPPFLAGS)" libleveldb.a

leveldb/libmemenv.a:
	@echo "Building LevelDB ..." && cd leveldb && CXX="$(CXX)" CC="$(CC)" \
	  PLATFORM=$(TARGET_OS) AR="$(AR)" $(MAKE) $(LEVELDB_TARGET_FLAGS) OPT="$(CXXFLAGS) $(CPPFLAGS)" libmemenv.a

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb secp256k1

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean 2>/dev/null
	rm -f leveldb/port/*.gcno leveldb/db/*.gcno leveldb/table/*.gcno leveldb/helpers/*.gcno
	rm -f leveldb/util/*.gcno leveldb/helpers/memenv/*.gcno
