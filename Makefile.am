ACLOCAL_AMFLAGS = -I build-aux/m4
SUBDIRS = src
.PHONY: deploy FORCE

if BUILD_FRIENDSHIPCOIN_LIBS
#pkgconfigdir = $(libdir)/pkgconfig
#pkgconfig_DATA = libdashconsensus.pc
endif

FRIENDSHIPCOIND_BIN=$(top_builddir)/src/friendshipcoind$(EXEEXT)
## FRIENDSHIPCOIN_QT_BIN=$(top_builddir)/src/qt/dash-qt$(EXEEXT)
## FRIENDSHIPCOIN_CLI_BIN=$(top_builddir)/src/dash-cli$(EXEEXT)
## FRIENDSHIPCOIN_WIN_INSTALLER=$(PACKAGE)-$(PACKAGE_VERSION)-win$(WINDOWS_BITS)-setup$(EXEEXT)

dist-hook:
	-$(MAKE) -C $(top_distdir)/src/leveldb clean
	-$(MAKE) -C $(top_distdir)/src/secp256k1 distclean
	-$(GIT) archive --format=tar HEAD -- src/clientversion.cpp | $(AMTAR) -C $(top_distdir) -xf -

distcheck-hook:
	$(MKDIR_P) $(top_distdir)/_build/src/leveldb
	cp -rf $(top_srcdir)/src/leveldb/* $(top_distdir)/_build/src/leveldb/
	-$(MAKE) -C $(top_distdir)/_build/src/leveldb clean

## distcleancheck:
	## @:

## $(FRIENDSHIPCOIN_WIN_INSTALLER): all-recursive
	## $(MKDIR_P) $(top_builddir)/release
	## STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(FRIENDSHIPCOIND_BIN) $(top_builddir)/release
	## STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(FRIENDSHIPCOIN_QT_BIN) $(top_builddir)/release
	## STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(FRIENDSHIPCOIN_CLI_BIN) $(top_builddir)/release
	## @test -f $(MAKENSIS) && $(MAKENSIS) -V2 $(top_builddir)/share/setup.nsi || \
	  ## echo error: could not build $@
	## @echo built $@

## $(if $(findstring src/,$(MAKECMDGOALS)),$(MAKECMDGOALS), none): FORCE
## 	$(MAKE) -C src $(patsubst src/%,%,$@)

## $(OSX_APP)/Contents/PkgInfo:
	## $(MKDIR_P) $(@D)
	## @echo "APPL????" > $@

## $(OSX_APP)/Contents/Resources/empty.lproj:
	## $(MKDIR_P) $(@D)
	## @touch $@ 

## $(OSX_APP)/Contents/Info.plist: $(OSX_PLIST)
	## $(MKDIR_P) $(@D)
	## $(INSTALL_DATA) $< $@

## $(OSX_APP)/Contents/Resources/friendshipcoin.icns: $(OSX_INSTALLER_ICONS)
	## $(MKDIR_P) $(@D)
	## $(INSTALL_DATA) $< $@

## $(OSX_APP)/Contents/MacOS/Dash-Qt: $(FRIENDSHIPCOIN_QT_BIN)
	## $(MKDIR_P) $(@D)
	## STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM)  $< $@

## $(OSX_APP)/Contents/Resources/Base.lproj/InfoPlist.strings: $(OSX_BASE_LPROJ_DIR)
	## $(MKDIR_P) $(@D)
	## $(INSTALL_DATA) $< $@

## OSX_APP_BUILT=$(OSX_APP)/Contents/PkgInfo $(OSX_APP)/Contents/Resources/empty.lproj \
  ## $(OSX_APP)/Contents/Resources/friendshipcoin.icns $(OSX_APP)/Contents/Info.plist \
  ## $(OSX_APP)/Contents/MacOS/Dash-Qt $(OSX_APP)/Contents/Resources/Base.lproj/InfoPlist.strings

## if BUILD_DARWIN
## $(OSX_DMG): $(OSX_APP_BUILT) $(OSX_PACKAGING)
	## $(OSX_DEPLOY_SCRIPT) $(OSX_APP) -add-qt-tr $(OSX_QT_TRANSLATIONS) -translations-dir=$(QT_TRANSLATION_DIR) -dmg -fancy $(OSX_FANCY_PLIST) -verbose 2
## 
## deploydir: $(OSX_DMG)
## else
## APP_DIST_DIR=$(top_builddir)/dist
## APP_DIST_EXTRAS=$(APP_DIST_DIR)/.background/$(OSX_BACKGROUND_IMAGE) $(APP_DIST_DIR)/.DS_Store $(APP_DIST_DIR)/Applications
## 
## $(APP_DIST_DIR)/Applications:
	## @rm -f $@
	## @cd $(@D); $(LN_S) /Applications $(@F)

## $(APP_DIST_EXTRAS): $(APP_DIST_DIR)/$(OSX_APP)/Contents/MacOS/Dash-Qt

## $(OSX_DMG): $(APP_DIST_EXTRAS)
	## $(GENISOIMAGE) -no-cache-inodes -D -l -probe -V "Dash-Core" -no-pad -r -dir-mode 0755 -apple -o $@ dist

## $(APP_DIST_DIR)/.background/$(OSX_BACKGROUND_IMAGE): contrib/macdeploy/$(OSX_BACKGROUND_IMAGE)
	## $(MKDIR_P) $(@D)
	## $(INSTALL) $< $@
## $(APP_DIST_DIR)/.DS_Store: contrib/macdeploy/DS_Store
	## $(INSTALL) $< $@
## 
## $(APP_DIST_DIR)/$(OSX_APP)/Contents/MacOS/Dash-Qt: $(OSX_APP_BUILT) $(OSX_PACKAGING)
	## INSTALLNAMETOOL=$(INSTALLNAMETOOL)  OTOOL=$(OTOOL) STRIP=$(STRIP) $(OSX_DEPLOY_SCRIPT) $(OSX_APP) -translations-dir=$(QT_TRANSLATION_DIR) -add-qt-tr $(OSX_QT_TRANSLATIONS) -verbose 2

## deploydir: $(APP_DIST_EXTRAS)
## endif

## if TARGET_DARWIN
## appbundle: $(OSX_APP_BUILT)
## deploy: $(OSX_DMG)
## endif
## if TARGET_WINDOWS
## deploy: $(FRIENDSHIPCOIN_WIN_INSTALLER)
## endif
 
## $(FRIENDSHIPCOIN_QT_BIN): FORCE
	## $(MAKE) -C src qt/$(@F)

$(FRIENDSHIPCOIND_BIN): FORCE
	$(MAKE) -C src $(@F)

## $(FRIENDSHIPCOIN_CLI_BIN): FORCE
	## $(MAKE) -C src $(@F)
# 
## if USE_LCOV
# 
## baseline.info:
	## $(LCOV) -c -i -d $(abs_builddir)/src -o $@
# 
## baseline_filtered.info: baseline.info
	## $(LCOV) -r $< "/usr/include/*" -o $@
# 
## leveldb_baseline.info: baseline_filtered.info
	## $(LCOV) -c -i -d $(abs_builddir)/src/leveldb -b $(abs_builddir)/src/leveldb -o $@
# 
## leveldb_baseline_filtered.info: leveldb_baseline.info
	## $(LCOV) -r $< "/usr/include/*" -o $@
# 
## baseline_filtered_combined.info: leveldb_baseline_filtered.info baseline_filtered.info
	## $(LCOV) -a leveldb_baseline_filtered.info -a baseline_filtered.info -o $@
# 
## test_dash.info: baseline_filtered_combined.info
	## $(MAKE) -C src/ check
	## $(LCOV) -c -d $(abs_builddir)/src -t test_dash -o $@
	## $(LCOV) -z -d $(abs_builddir)/src
	## $(LCOV) -z -d $(abs_builddir)/src/leveldb
# 
## test_dash_filtered.info: test_dash.info
	## $(LCOV) -r $< "/usr/include/*" -o $@
# 
## block_test.info: test_dash_filtered.info
	## $(MKDIR_P) qa/tmp
	## -@TIMEOUT=15 qa/pull-tester/run-friendshipcoind-for-test.sh $(JAVA) -jar $(JAVA_COMPARISON_TOOL) qa/tmp/compTool $(COMPARISON_TOOL_REORG_TESTS)
	## $(LCOV) -c -d $(abs_builddir)/src --t FriendshipcoinJBlockTest -o $@
	## $(LCOV) -z -d $(abs_builddir)/src
	## $(LCOV) -z -d $(abs_builddir)/src/leveldb

## block_test_filtered.info: block_test.info
	## $(LCOV) -r $< "/usr/include/*" -o $@

## rpc_test.info: test_dash_filtered.info
	## -@TIMEOUT=15 python qa/pull-tester/rpc-tests.py $(EXTENDED_RPC_TESTS)
	## $(LCOV) -c -d $(abs_builddir)/src --t rpc-tests -o $@
	## $(LCOV) -z -d $(abs_builddir)/src
	## $(LCOV) -z -d $(abs_builddir)/src/leveldb

## rpc_test_filtered.info: rpc_test.info
	## $(LCOV) -r $< "/usr/include/*" -o $@

## test_dash_coverage.info: baseline_filtered_combined.info test_dash_filtered.info
	## $(LCOV) -a baseline_filtered.info -a leveldb_baseline_filtered.info -a test_dash_filtered.info -o $@
## 
## total_coverage.info: baseline_filtered_combined.info test_dash_filtered.info block_test_filtered.info rpc_test_filtered.info
	## $(LCOV) -a baseline_filtered.info -a leveldb_baseline_filtered.info -a test_dash_filtered.info -a block_test_filtered.info -a rpc_test_filtered.info -o $@ | $(GREP) "\%" | $(AWK) '{ print substr($$3,2,50) "/" $$5 }' > coverage_percent.txt

## test_dash.coverage/.dirstamp:  test_dash_coverage.info
	## $(GENHTML) -s $< -o $(@D)
	## @touch $@

## total.coverage/.dirstamp: total_coverage.info
	## $(GENHTML) -s $< -o $(@D)
	## @touch $@

## cov: test_dash.coverage/.dirstamp total.coverage/.dirstamp

## endif

# Dash: disable the test until upstream switches from convoluted comparison tool
# Ref https://github.com/friendshipcoin/friendshipcoin/issues/4545
if USE_COMPARISON_TOOL
check-local:
	## $(MKDIR_P) qa/tmp
	## @qa/pull-tester/run-friendshipcoind-for-test.sh $(JAVA) -jar $(JAVA_COMPARISON_TOOL) qa/tmp/compTool $(COMPARISON_TOOL_REORG_TESTS) 2>&1
endif

dist_noinst_SCRIPTS = autogen.sh

## EXTRA_DIST = $(top_srcdir)/share/genbuild.sh qa/pull-tester/rpc-tests.py qa/rpc-tests $(DIST_DOCS) $(WINDOWS_PACKAGING) $(OSX_PACKAGING) $(BIN_CHECKS)

EXTRA_DIST = $(top_srcdir)/share/genbuild.sh

## CLEANFILES = $(OSX_DMG) $(FRIENDSHIPCOIN_WIN_INSTALLER)

.INTERMEDIATE: $(COVERAGE_INFO)

clean-local:
	rm -rf coverage_percent.txt test_friendshipcoin.coverage/ total.coverage/ qa/tmp/ cache/ #$(OSX_APP)
