test_sources = [
    'source.cpp',
    'tests/UUIDtest.cpp',
]

test_dependencies = [
    catch2_dep,
    cpp_libuuid_dep,
]

message(cpp_libuuid_link)

testexe = executable('testexe', test_sources,
                     dependencies: test_dependencies)

test_args = []

if get_option('test_report')
    message('using JUnit XML report output')
    test_args += [
        '--reporter xml'
    ]
endif


test('libuuid unit tests', testexe, args: test_args)