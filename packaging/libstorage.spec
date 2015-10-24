Name:       libstorage
Summary:    Library to get storage information
Version:    0.1.0
Release:    0
Group:      System/Libraries
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
Source1:    %{name}.manifest
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(glib-2.0)

%description
development package of library to get storage

%package devel
Summary:	Get storage information (devel)
Group:		Development/Libraries
Requires:	%{name} = %{version}-%{release}

%description devel
Library to get storage information (devel)


%prep
%setup -q

%build
%if 0%{?tizen_build_binary_release_type_eng}
export CFLAGS+=" -DTIZEN_ENGINEER_MODE"
%endif
CFLAGS="$CFLAGS" cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}
%make_install
cp -a %{SOURCE1} %{buildroot}%{_datadir}/

%post

%postun

%files
%{_libdir}/*.so.*
%{_sysconfdir}/storage/libstorage.conf
%{_datadir}/license/%{name}
%manifest %{_datadir}/%{name}.manifest

%files devel
%{_includedir}/storage/*.h
%{_libdir}/*.so
%{_libdir}/pkgconfig/*.pc
