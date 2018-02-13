const path = require('path');
const merge = require('webpack-merge');
const common = require('./webpack.common.js');

module.exports = merge(common, {
    devServer: {
        contentBase: path.join(__dirname, "build"),
        compress: true,
        hot: false,
        historyApiFallback: true,
        port: 9000
    },
    devtool: 'source-map',
});