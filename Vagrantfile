# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/focal64"

  config.vm.provider :virtualbox do |v|
    v.gui = true
    v.memory = 8192
    v.cpus = 4
  end

  #config.vm.synced_folder ".", "/home/vagrant/px4"

  config.vm.provision 'shell', inline: <<-EOF
#!/bin/sh
set -e
export DEBIAN_FRONTEND=noninteractive

sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get install -y --no-install-recommends ubuntu-desktop
sudo apt-get install -y --no-install-recommends virtualbox-guest-dkms virtualbox-guest-utils virtualbox-guest-x11 virtualbox-guest-additions-iso
sudo usermod -a -G sudo vagrant
sudo apt-get install -y firefox

TEMP_DEB="$(mktemp)"
wget -q -O "$TEMP_DEB" https://github.com/mavlink/MAVSDK/releases/download/v0.29.0/mavsdk_0.29.0_ubuntu20.04_amd64.deb
sudo dpkg -i "$TEMP_DEB"
rm -f "$TEMP_DEB"

sudo apt-get install -y --no-install-recommends \
    net-tools \
    astyle \
    build-essential \
    ccache \
    cmake \
    cppcheck \
    file \
    g++ \
    gcc \
    gdb \
    git \
    lcov \
    make \
    ninja-build \
    python3 \
    python3-dev \
    python3-pip \
    python3-setuptools \
    python3-wheel \
    rsync \
    shellcheck \
    unzip \
    zip \
    bc \
    ;

sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
sudo apt-get install -y --no-install-recommends \
    dmidecode \
    gazebo9 \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-libav \
    libeigen3-dev \
    libgazebo9-dev \
    libgstreamer-plugins-base1.0-dev \
    libimage-exiftool-perl \
    libopencv-dev \
    libxml2-utils \
    pkg-config \
    protobuf-compiler \
    ;

sudo pip3 install \
    argcomplete \
    argparse \
    cerberus \
    coverage \
    empy \
    jinja2 \
    matplotlib \
    numpy \
    packaging \
    pandas \
    pkgconfig \
    psutil \
    pygments \
    pyros-genmsg \
    pyserial \
    pyulog \
    pyyaml \
    requests \
    setuptools \
    six \
    toml \
    wheel \
    ;

sudo shutdown -r now
EOF

end
