# Extends the default builder to add the required SDK hacks
FROM ghcr.io/ledgerhq/ledger-app-builder/ledger-app-builder:latest

# Hack the keyboard bottom alignment
RUN sed -i 's#keyboard->alignmentMarginY = 60;#keyboard->alignmentMarginY = 1;#g' /opt/stax-secure-sdk/lib_nbgl/src/nbgl_layout.c
