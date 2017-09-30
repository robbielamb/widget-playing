include Utils;

let component = ReasonReact.statelessComponent "BreadCrumb";

let make
    tag::(tag: string)="ol"
    className::(className: option string)=?
    /* cssModule::(cssModule: option (Js.t {..}))=? */
    children => {
  ...component,
  render: fun _self => {
    let classes = classNameReduce className [cn "breadcrumb"];
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
      let classes = classNameReduce className [cn "breadcrumb-item", ocn ("active", active)];
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};