pandoc "D:\MyBlogs\Hexo\source\_posts\算法\数论\exMusic.md" `
  --from=markdown+yaml_metadata_block+tex_math_dollars+tex_math_double_backslash+raw_tex `
  --pdf-engine=xelatex `
  --template "D:\MyBlogs\pandoc-xcpc-win-safe.tex" `
  --lua-filter "D:\MyBlogs\rewrite-images.lua" `
  --resource-path="D:\MyBlogs\Hexo\source;D:\MyBlogs\Hexo\source\_posts;D:\MyBlogs\Hexo\source\image" `
  -o "D:\MyBlogs\PDF\_test.pdf"
