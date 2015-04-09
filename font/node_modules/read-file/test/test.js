/**
 * read-file <https://github.com/assemble/read-file>
 *
 * Copyright (c) 2014 Jon Schlinkert, contributors.
 * Licensed under the MIT license.
 */

const expect = require('chai').expect;
const path = require('path');
const file = require('../');

describe('file system methods', function () {

  var testTxtFile = 'test/fixtures/test.txt';
  var testTxtContents = 'FILE CONTENTS!!!';

  it('should read the file', function () {
    var expected = testTxtContents;
    var actual = file.readFileSync(testTxtFile);
    expect(actual).to.eql(expected);
  });

  it('should read the file (async)', function (done) {
    var expected = testTxtContents;
    file.readFile(testTxtFile, function (err, actual) {
      expect(actual).to.eql(expected);
      done();
    });
  });
});