var gulp  = require('gulp')
var shell = require('gulp-shell')
var watch = require('gulp-watch')

gulp.task('compile', shell.task([
  'clear',
  'make clean',
  // 'make osp2a',
  // './osp2a Lorem ipsum dolor sit amet, consectetur adipisicing elit. Amet, possimus! 2421',
  // 'echo',
]))

gulp.task('watch', function() {
    gulp.watch('./*.c', ['compile']);
    gulp.watch('./*.h', ['compile']);
});

gulp.task('default' ,function() {
    gulp.watch('./*.c', ['compile']);
    gulp.watch('./*.h', ['compile']);
});
