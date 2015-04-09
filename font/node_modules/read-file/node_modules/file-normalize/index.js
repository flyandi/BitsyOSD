/**
 * file-normalize <https://github.com/assemble/file-normalize>
 *
 * Copyright (c) 2014 Jon Schlinkert, Brian Woodward, contributors.
 * Licensed under the MIT license.
 */
'use strict';

var os = require('os');
var file = module.exports = {};


/**
 * ## .pathSepRegex
 *
 * Normalize paths to use `/`
 *
 * @type  {RegExp}
 * @return {N/A}
 */

file.pathSepRegex = /[\/\\]/g;
file.normalizeSlash = function(str) {
  return str.replace(file.pathSepRegex, '/');
};

/**
 * ## .normalizeEOL( str )
 *
 * Normalize line endings to use the defaults of the current operating system.
 *
 * @param   {String} `str`
 * @return  {String}
 */

file.normalizeEOL = function(str) {
  return str.replace(/\r\n|\n/g, os.EOL);
};

/**
 * ## .normalizeNL( str )
 *
 * Normalize all line endings to newlines, `\n`.
 *
 * ```js
 * var file = require('read-file');
 * var str = file.readFileSync('foo.txt');
 * file.normalizeNL(str);
 * ```
 *
 * @param   {String} `str`
 * @return  {String}
 */

file.normalizeNL = function(str) {
  return str.replace(/\r\n|\n/g, '\n');
};

/**
 * ## .encoding( encoding )
 *
 * Encoding to use. Default is `utf8`.
 *
 * @param   {String} `encoding`
 * @return  {String}
 */

file.encoding = function(encoding) {
  return encoding || 'utf8';
};

/**
 * ## .preserveBOM
 *
 * Preserve byte order marks. Default is `false`.
 *
 * **Example:**
 *
 * ```js
 * var file = require('file-normalize');
 * file.preserveBOM = true;
 * ```
 *
 * @return  {N/A}
 */

file.preserveBOM = false;

/**
 * ## .stripBOM( str )
 *
 * Strip byte order marks.
 *
 * **Example:**
 *
 * ```js
 * var file = require('read-file');
 * var str = file.readFileSync('foo.txt');
 * file.stripBOM(str);
 * ```
 *
 * @param   {String} `str`
 * @return  {String}
 */

file.stripBOM = function(str) {
  // Transform EOL
  var contents = (os.EOL === '\n') ? str : str.replace(os.EOL, '\n');
  // Strip UTF BOM
  if (!file.preserveBOM && contents.charCodeAt(0) === 0xFEFF) {
    contents = contents.substring(1);
    contents = contents.replace(/^\uFEFF/, '');
  }
  return contents;
};
