[%bs.raw {|require('bootstrap/dist/css/bootstrap.css')|}];

[%bs.raw {|require('highlight.js/styles/default.css')|}];

[%bs.raw {|require('highlight.js/styles/solarized-dark.css')|}];

/* [@bs.module "./registerServiceWorker"] external register_service_worker : unit => unit = "default"; */

ReactDOMRe.renderToElementWithId(<Shell />, "root");

/* register_service_worker(); */
