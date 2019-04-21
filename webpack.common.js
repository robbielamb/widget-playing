const path = require('path');
const CopyWebpackPlugin = require('copy-webpack-plugin');
const ExtractTextPlugin = require('extract-text-webpack-plugin');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const webpack = require('webpack');

module.exports = {
  entry: path.join(__dirname, 'example/index.bs.js'),
  output: {
    path: path.join(__dirname, "build"),
    filename: 'js/app.js',
    publicPath: '/'
  }, 
  module: {
    rules: [
      {
        test: /\.(re)$/,
        loader: 'raw-loader'
      },
      {
        test: /\.(eot|ttf|woff|woff2|svg)$/,
        loader: 'file-loader?name=fonts/[name].[ext]'
      },
      {
        test: /\.(css|scss)$/,
        loader: ExtractTextPlugin.extract({
          use: [{
            loader: "css-loader"
          }, {
            loader: "sass-loader"
          }],
          fallback: 'style-loader'
        })
      }
    ]
  },
  resolve: {
    alias: {
        Examples: path.join(__dirname, "example")
    },
    extensions: ['.re', '.ml', '.js']
  },
  plugins: [
    // extract CSS into a separate file
    new ExtractTextPlugin({ filename: 'css/app.css', allChunks: true }),

    // Can this be mangled?
    new HtmlWebpackPlugin({
      template: 'public/index.html',
      inject: 'body',
      filename: 'index.html'
    }),

    new CopyWebpackPlugin([{ from: path.join(__dirname, 'public'), ignore: ['index.html'] }]),

    new webpack.optimize.ModuleConcatenationPlugin(),

    new webpack.DefinePlugin({
        RE_PATH: JSON.stringify(path.join(__dirname, "example"))
    })
  ],
};
