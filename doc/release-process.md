Release Process
====================

Before every release candidate:

* Update translations (ping wumpus on IRC) see [translation_process.md](https://github.com/friendshipcoin/friendshipcoin/blob/master/doc/translation_process.md#synchronising-translations).

Before every minor and major release:

* Update [bips.md](bips.md) to account for changes since the last release.
* Update version in sources (see below)
* Write release notes (see below)

Before every major release:

* Update hardcoded [seeds](/contrib/seeds/README.md), see [this pull request](https://github.com/friendshipcoin/friendshipcoin/pull/7415) for an example.

### First time / New builders

Check out the source code in the following directory hierarchy.

    cd /path/to/your/toplevel/build
    git clone https://github.com/friendshipcoin/friendshipcoin-core.git

### Friendshipcoin maintainers/release engineers, update version in sources

Update the following:

- `configure.ac`:
    - `_CLIENT_VERSION_MAJOR`
    - `_CLIENT_VERSION_MINOR`
    - `_CLIENT_VERSION_REVISION`
    - Don't forget to set `_CLIENT_VERSION_IS_RELEASE` to `true`
- `src/clientversion.h`: (this mirrors `configure.ac` - see issue #3539)
    - `CLIENT_VERSION_MAJOR`
    - `CLIENT_VERSION_MINOR`
    - `CLIENT_VERSION_REVISION`
    - Don't forget to set `CLIENT_VERSION_IS_RELEASE` to `true`
- `doc/README.md` and `doc/README_windows.txt`
- `doc/Doxyfile`: `PROJECT_NUMBER` contains the full version
- `contrib/gitian-descriptors/*.yml`: usually one'd want to do this on master after branching off the release - but be sure to at least do it before a new major release

Write release notes. git shortlog helps a lot, for example:

    git shortlog --no-merges v(current version, e.g. 4.0.6)..v(new version, e.g. 4.1.0)

(or ping @wumpus on IRC, he has specific tooling to generate the list of merged pulls
and sort them into categories based on labels)

Generate list of authors:

    git log --format='%aN' "$*" | sort -ui | sed -e 's/^/- /'

Tag version (or release candidate) in git

    git tag -s v(new version, e.g. 4.1.0)

### Setup and perform Gitian builds

Setup Gitian descriptors:

    pushd ./friendshipcoin-core
    export VERSION=(new version, e.g. v4.1.0)
    git fetch
    git checkout v${VERSION}
    popd

Ensure gitian-builder is up-to-date:

    pushd ./gitian-builder
    git pull
    popd

### Fetch and create inputs: (first time, or when dependency versions change)

    pushd ./gitian-builder
    mkdir -p inputs
    wget -P inputs https://bitcoincore.org/cfields/osslsigncode-Backports-to-1.7.1.patch
    wget -P inputs http://downloads.sourceforge.net/project/osslsigncode/osslsigncode/osslsigncode-1.7.1.tar.gz
    popd

Create the OS X SDK tarball, see the [OS X readme](README_osx.md) for details, and copy it into the inputs directory.

### Optional: Seed the Gitian sources cache and offline git repositories

By default, Gitian will fetch source files as needed. To cache them ahead of time:

    pushd ./gitian-builder
    make -C ../friendshipcoin-core/depends download SOURCES_PATH=`pwd`/cache/common
    popd

Only missing files will be fetched, so this is safe to re-run for each build.

NOTE: Offline builds must use the --url flag to ensure Gitian fetches only from local URLs. For example:

    pushd ./gitian-builder
    ./bin/gbuild --url friendshipcoin-core=/path/to/friendshipcoin,signature=/path/to/sigs {rest of arguments}
    popd

The gbuild invocations below <b>DO NOT DO THIS</b> by default.

### Build and sign Friendshipcoin Core for Linux, Windows, and OS X:

    pushd ./gitian-builder
    ./bin/gbuild --memory 3000 --commit friendshipcoin-core=${VERSION} ../friendshipcoin-core/contrib/gitian-descriptors/gitian-linux.yml
    mv build/out/friendshipcoin-*.tar.gz build/out/src/friendshipcoin-*.tar.gz ../

    ./bin/gbuild --memory 3000 --commit friendshipcoin-core=${VERSION} ../friendshipcoin-core/contrib/gitian-descriptors/gitian-win.yml
    mv build/out/friendshipcoin-*-win-unsigned.tar.gz inputs/friendshipcoin-win-unsigned.tar.gz
    mv build/out/friendshipcoin-*.zip build/out/friendshipcoin-*.exe ../

    ./bin/gbuild --memory 3000 --commit friendshipcoin-core=${VERSION} ../friendshipcoin-core/contrib/gitian-descriptors/gitian-osx.yml
    mv build/out/friendshipcoin-*-osx-unsigned.tar.gz inputs/friendshipcoin-osx-unsigned.tar.gz
    mv build/out/friendshipcoin-*.tar.gz build/out/friendshipcoin-*.dmg ../
    popd

Build output expected:

  1. source tarball (`friendshipcoin-${VERSION}.tar.gz`)
  2. linux 32-bit and 64-bit dist tarballs (`friendshipcoin-${VERSION}-linux[32|64].tar.gz`)
  3. windows 32-bit and 64-bit unsigned installers and dist zips (`friendshipcoin-${VERSION}-win[32|64]-setup-unsigned.exe`, `friendshipcoin-${VERSION}-win[32|64].zip`)
  4. OS X unsigned installer and dist tarball (`friendshipcoin-${VERSION}-osx-unsigned.dmg`, `friendshipcoin-${VERSION}-osx64.tar.gz`)
  5. Gitian signatures (in `gitian.sigs/${VERSION}-<linux|{win,osx}-unsigned>/(your Gitian key)/`)


The list of files should be:
```
friendshipcoin-${VERSION}-aarch64-linux-gnu.tar.gz
friendshipcoin-${VERSION}-arm-linux-gnueabihf.tar.gz
friendshipcoin-${VERSION}-i686-pc-linux-gnu.tar.gz
friendshipcoin-${VERSION}-x86_64-linux-gnu.tar.gz
friendshipcoin-${VERSION}-osx64.tar.gz
friendshipcoin-${VERSION}-osx.dmg
friendshipcoin-${VERSION}.tar.gz
friendshipcoin-${VERSION}-win32-setup.exe
friendshipcoin-${VERSION}-win32.zip
friendshipcoin-${VERSION}-win64-setup.exe
friendshipcoin-${VERSION}-win64.zip
```
The `*-debug*` files generated by the gitian build contain debug symbols
for troubleshooting by developers. It is assumed that anyone that is interested
in debugging can run gitian to generate the files for themselves. To avoid
end-user confusion about which file to pick, as well as save storage
space *do not upload these to the friendshipcoin.org server, nor put them in the torrent*.

- GPG-sign it, delete the unsigned file:
```
gpg --digest-algo sha256 --clearsign SHA256SUMS # outputs SHA256SUMS.asc
rm SHA256SUMS
```
(the digest algorithm is forced to sha256 to avoid confusion of the `Hash:` header that GPG adds with the SHA256 used for the files)
Note: check that SHA256SUMS itself doesn't end up in SHA256SUMS, which is a spurious/nonsensical entry.

- Upload zips and installers, as well as `SHA256SUMS.asc` from last step, to the friendshipcoin.org server
  into `/var/www/bin/friendshipcoin-core-${VERSION}`

- A `.torrent` will appear in the directory after a few minutes. Optionally help seed this torrent. To get the `magnet:` URI use:
```bash
transmission-show -m <torrent file>
```
Insert the magnet URI into the announcement sent to mailing lists. This permits
people without access to `friendshipcoin.org` to download the binary distribution.
Also put it into the `optional_magnetlink:` slot in the YAML file for
friendshipcoin.org (see below for friendshipcoin.org update instructions).

- Update friendshipcoin.org version

- Announce the release:

- Celebrate
