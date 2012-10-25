#import('dart:io', prefix: 'io');
#import('package:unittest/unittest.dart');

#import('../lib/svn.dart', prefix: 'svn');

testFirst() {
  expect(svn.getVersion(), "1.7.6");
  expect(svn.SvnVersion.major, 1);
  expect(svn.SvnVersion.minor, 7);
  expect(svn.SvnVersion.patch, 6);
}

main() {
  test('Version', () =>
  expect(svn.getVersion(), "1.7.6"));
  print("All tests pass!");
  testFirst();
  test('First', testFirst);
}

