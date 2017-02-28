var gulp  = require('gulp')
var shell = require('gulp-shell')
var watch = require('gulp-watch')

gulp.task('compile', shell.task([
  'clear',
  'make clean',
  'make osp2a',
  'echo',
  'echo "Test case 1"',
  './osp2a "Lorem ipsum dolor sit amet, consectetur adipisicing elit. Amet, possimus! 2421"',
  'echo',
  'echo "Test case 2"',
  './osp2a Lorem ipsum dolor "sit amet, consectetur" adipisicing elit. Amet, possimus! 2421',
  'echo',
  'echo "Test case 3"',
  './osp2a Lorem ipsum dolor sit amet, consectetur adipisicing elit. Amet, possimus! 2421',
  'echo',
  'echo "Test case 4"',
  './osp2a Lorem ipsum """""" 2421',
]))

gulp.task('watch', function() {
    gulp.watch('./*.c', ['compile']);
    gulp.watch('./*.h', ['compile']);
});

gulp.task('default' ,function() {
    gulp.watch('./*.c', ['compile']);
    gulp.watch('./*.h', ['compile']);
});
