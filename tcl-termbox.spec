%{!?directory:%define directory /usr}

%define buildroot %{_tmppath}/%{name}
%define packname  termbox

Name:          tcl-termbox
Summary:       Tcl bindings for termbox
Version:       0.1
Release:       1
License:       MIT
Group:         Development/Libraries/Tcl
Source:        %{name}-%{version}.tar.gz
URL:           https://github.com/ray2501/tcl-termbox
BuildRequires: autoconf
BuildRequires: make
BuildRequires: tcl-devel >= 8.5
Requires:      tcl >= 8.5
BuildRoot:     %{buildroot}

%description
This package is Tcl bindings for termbox.

termbox is a minimal, legacy-free alternative to ncurses,
suitable for building text-based user interfaces.

%prep
%setup -q -n %{name}-%{version}

%build
CFLAGS="%optflags" ./configure \
	--prefix=%{directory} \
	--exec-prefix=%{directory} \
	--libdir=%{directory}/%{_lib}
make 

%install
make DESTDIR=%{buildroot} pkglibdir=%{tcl_archdir}/%{packname}%{version} install

%clean
rm -rf %buildroot

%files
%defattr(-,root,root)
%doc README.md LICENSE
%{tcl_archdir}
