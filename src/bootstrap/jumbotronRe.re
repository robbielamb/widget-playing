include Utils;

let component = ReasonReact.statelessComponent "Jumbotron";

let make
    fluid::(fluid: bool)=false
    tag::(tag: string)="div"
    className::(className: option string)=?
    /* cssModule::(cssModule: option (Js.t {..}))=? */
    children => {
  ...component,
  render: fun _self => {
    let classes =
      ["jumbotron", fluid ? "jumbotron-fluid" : "", unwrapStr i className] |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  }
};