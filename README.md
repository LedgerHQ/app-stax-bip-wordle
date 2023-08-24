# BIP Wordle game for Stax

## Getting started using Docker Compose

```shell
# Build containers
docker compose build
# Build the app
docker compose run builder
# Lauch the simulator
docker compose run speculos
```

### Environment

You might need the following environement variable:

- `UID=$(id -u)` (only required if your `uid` is not 1000)
- `GID=$(id -g)` (only required if your `gid` is not 1000)
- `XDG_RUNTIME_DIR` (should already be set)
- `WAYLAND_DISPLAY` (should already be set)

## Manual installation

```shell
# Get speculos:
git clone https://github.com/LedgerHQ/speculos
# Build it
cmake -Bbuild -H. && make -C build
# Prepare virtual env
python -m venv venv && source venv/bin/activate && pip install --upgrade pip && pip install .
# Get the sample game app
git clone git@github.com:LedgerHQ/app-hello-world.git --branch rebound_game
# Pull docker app builder
docker pull ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest
# Build the app
sudo docker run --rm -ti --user "$(id -u):$(id -g)" --privileged -v "/dev/bus/usb:/dev/bus/usb" -v "$(realpath .):/app" ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest bash -c "make BOLOS_SDK=\$STAX_SDK DEBUG=1"
# Run the app in speculos (with venv enabled)
../speculos/speculos.py --model stax --ontop ./bin/app.elf
# Or build and sideload the app on a real device (need to use root user: 0)
sudo docker run --rm -ti --user "0:0" --privileged -v "/dev/bus/usb:/dev/bus/usb" -v "$(realpath .):/app" ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest bash -c "make BOLOS_SDK=\$STAX_SDK DEBUG=0 clean all load"
```
