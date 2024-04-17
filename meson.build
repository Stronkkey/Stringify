project(
  'stringify',
  'cpp',
  version : '1.0.0',
  default_options : ['warning_level=0', 'cpp_std=c++17'])

project_description = 'A header only string conversion library'

public_headers = include_directories('include')

project_target = shared_library(
  meson.project_name(),
  [],
  install: true,
  include_directories: public_headers
)

_ = [project_target]

project_dependency = declare_dependency(
  include_directories: public_headers
)

set_variable(meson.project_name() + '_dep', project_dependency)

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : meson.project_name(),
  filebase : meson.project_name(),
  description : project_description,
  subdirs : meson.project_name(),
)

exe = executable(
  meson.project_name(),
  files('main.cpp'),
  dependencies: [],
  install: false
)
