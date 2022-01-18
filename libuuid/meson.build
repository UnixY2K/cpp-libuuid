cpp_libuuid_inc = include_directories('include')

cpp_libuuid_srcs = []
cpp_libuuid_args = []
cpp_libuuid_link = []
cpp_libuuid_deps = []

# linux needs libuuid
if host_machine.system() == 'linux'
    libuuid = dependency('uuid', required: true)
    cpp_libuuid_deps += libuuid
endif

cpp_libuuid_dep = declare_dependency(
    include_directories: cpp_libuuid_inc,
    dependencies: cpp_libuuid_deps
)
