
# TEST: proj test sub module

add_test_exe    (tVersion tVersion.c)
test_link_libs  (tVersion ${CBASE})
create_test     (tVersion)
