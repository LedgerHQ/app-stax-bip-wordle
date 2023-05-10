# BIP Wordle game for Stax

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
```

```shell
# Patch the Stax SDK to lower the keyboard on the screen to get rid of the 60px footer imposed by the SDK
sudo docker run --rm -ti --user "0:0" --privileged \
    -v "/dev/bus/usb:/dev/bus/usb" -v "$(realpath .):/app" \
    ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest \
    bash -c "\
        sed -i 's#keyboard->alignmentMarginY = 60;#keyboard->alignmentMarginY = 0;#g' /opt/stax-secure-sdk/lib_nbgl/src/nbgl_layout.c && \
        make BOLOS_SDK=\$STAX_SDK DEBUG=1 \
    "
```
