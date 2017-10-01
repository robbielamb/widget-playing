include Utils;

let component = ReasonReact.statelessComponent "BreadCrumb";

let make
    tag::(tag: string)="ol"
    className::(className: option string)=?
    /* cssModule::(cssModule: option (Js.t {..}))=? */
    children => {
  ...component,
  render: fun _self => {
    let classes = ["breadcrumb", unwrapStr i className] |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  }
};

module Item = {
  let component = ReasonReact.statelessComponent "BreadCrumb.Item";
  let make
      active::(active: bool)=false
      tag::(tag: string)="li"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children => {
    ...component,
    render: fun _self => {
      let classes =
        ["breadcrumb-item", active ? "active" : "", unwrapStr i className] |> String.concat " ";
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};