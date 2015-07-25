
# TEST: proj test sub module

add_test_exe    (tVersion tVersion.c)
test_link_libs  (tVersion ${CBASE})
create_test     (tVersion)

add_test_exe    (tInts tInts.c)
test_link_libs  (tInts )
create_test     (tInts)

add_test_exe    (tUtf8 tUtf8.c)
test_link_libs  (tUtf8 ${CBASE})
create_test     (tUtf8)

