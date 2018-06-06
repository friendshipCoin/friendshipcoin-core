ACLOCAL_AMFLAGS = -I build-aux/m4
SUBDIRS = src
.PHONY: deploy

if USE_LIBSECP256K1
secp256k1/libsecp256k1.la: $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	@$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
endif

GZIP_ENV="-9n"

FRIENDSHIPCOIND_BIN=$(top_builddir)/src/friendshipcoind$(EXEEXT)

COVERAGE_INFO = baseline_filtered_combined.info baseline.info block_test.info \
  leveldb_baseline.info test_friendshipcoin_filtered.info total_coverage.info \
  baseline_filtered.info block_test_filtered.info \
  leveldb_baseline_filtered.info test_friendshipcoin_coverage.info test_friendshipcoin.info

dist-hook:
	-$(MAKE) -C $(top_distdir)/src/leveldb clean
	-$(GIT) archive --format=tar HEAD -- src/version.cpp | $(AMTAR) -C $(top_distdir) -xf -

distcheck-hook:
	$(MKDIR_P) $(top_distdir)/_build/src/leveldb
	cp -rf $(top_srcdir)/src/leveldb/* $(top_distdir)/_build/src/leveldb/
	-$(MAKE) -C $(top_distdir)/_build/src/leveldb clean

distcleancheck:
	@:

$(FRIENDSHIPCOIND_BIN):
	make -C $(top_srcdir)/src friendshipcoind$(EXEEXT)

if USE_LCOV

baseline.info:
	$(LCOV) -c -i -d $(abs_builddir)/src -o $@

baseline_filtered.info: baseline.info
	$(LCOV) -r $< "/usr/include/*" -o $@

leveldb_baseline.info: baseline_filtered.info
	$(LCOV) -c -i -d $(abs_builddir)/src/leveldb -b $(abs_builddir)/src/leveldb -o $@

leveldb_baseline_filtered.info: leveldb_baseline.info
	$(LCOV) -r $< "/usr/include/*" -o $@

baseline_filtered_combined.info: leveldb_baseline_filtered.info baseline_filtered.info
	$(LCOV) -a leveldb_baseline_filtered.info -a baseline_filtered.info -o $@

test_friendshipcoin.info: baseline_filtered_combined.info
	$(MAKE) -C src/ check
	$(LCOV) -c -d $(abs_builddir)/src -t test_friendshipcoin -o $@
	$(LCOV) -z -d $(abs_builddir)/src
	$(LCOV) -z -d $(abs_builddir)/src/leveldb

test_friendshipcoin_filtered.info: test_friendshipcoin.info
	$(LCOV) -r $< "/usr/include/*" -o $@

block_test.info: test_friendshipcoin_filtered.info
	-@TIMEOUT=15 qa/pull-tester/run-friendshipcoind-for-test.sh $(JAVA) -Xmx2G -jar $(JAVA_COMPARISON_TOOL) 1 18444
	$(LCOV) -c -d $(abs_builddir)/src --t FriendshipcoinJBlockTest -o $@
	$(LCOV) -z -d $(abs_builddir)/src
	$(LCOV) -z -d $(abs_builddir)/src/leveldb

block_test_filtered.info: block_test.info
	$(LCOV) -r $< "/usr/include/*" -o $@

test_friendshipcoin_coverage.info: baseline_filtered_combined.info test_friendshipcoin_filtered.info
	$(LCOV) -a baseline_filtered.info -a leveldb_baseline_filtered.info -a test_friendshipcoin_filtered.info -o $@

total_coverage.info:  baseline_filtered_combined.info test_friendshipcoin_filtered.info block_test_filtered.info
	$(LCOV) -a baseline_filtered.info -a leveldb_baseline_filtered.info -a test_friendshipcoin_filtered.info -a block_test_filtered.info -o $@ | $(GREP) "\%" | $(AWK) '{ print substr($$3,2,50) "/" $$5 }' > coverage_percent.txt

test_friendshipcoin.coverage/.dirstamp:  test_friendshipcoin_coverage.info
	$(GENHTML) -s $< -o $(@D)
	@touch $@

total.coverage/.dirstamp: total_coverage.info
	$(GENHTML) -s $< -o $(@D)
	@touch $@

cov: test_friendshipcoin.coverage/.dirstamp total.coverage/.dirstamp

endif

if USE_COMPARISON_TOOL
check-local:
	@qa/pull-tester/run-friendshipcoind-for-test.sh $(JAVA) -Xmx2G -jar $(JAVA_COMPARISON_TOOL) 1 18444
endif

.INTERMEDIATE: $(COVERAGE_INFO)

clean-local:
	rm -rf test_friendshipcoin.coverage/ total.coverage/
