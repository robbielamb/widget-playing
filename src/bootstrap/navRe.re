include Utils;

/* This could have more option and classes applied! */
let component = ReasonReact.statelessComponent "ModalFooter";

let make
    tabs::(tabs: bool)=false
    pills::(pills: bool)=false
    vertical::(vertical: bool)=false
    justified::(justified: bool)=false
    navbar::(navbar: bool)=false
    tag::(tag: string)="ul"
    className::(className: option string)=?
    /* cssModule::(cssModule: option (Js.t {..}))=? */ children => {
  ...component,
  render: fun _self => {
    let classes =
      classNameReduce
        className
        [
          ocn ("navbar-nav", navbar),
          ocn ("nav", not navbar),
          ocn ("nav-tabs", tabs),
          ocn ("nav-pills", pills),
          ocn ("nav-justified", justified),
          ocn ("flex-column", vertical)
        ];
    ReasonReact.createDomElement tag props::{"className": classes} children
  }
};

/* TODO: Make a general 'dropdown' component first */
/* module NavDropdown = {
     external navDropdown : ReasonReact.reactClass = "NavDropdown" [@@bs.module "reactstrap"];
     let make
         tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
         className::(className: option string)=?
         cssModule::(cssModule: option (Js.t {..}))=?
         children =>
       ReasonReact.wrapJsForReason
         reactClass::navDropdown
         props::{
           "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
           "className": Js.Null_undefined.from_opt className,
           "cssModule": Js.Null_undefined.from_opt cssModule
         }
         children;
   }; */
module Item = {
  let component = ReasonReact.statelessComponent "Nav.Item";
  let make
      tag::(tag: string)="li"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */ children => {
    ...component,
    render: fun _self => {
      let classes = classNameReduce className [cn "nav-item"];
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module Link = {
  let component = ReasonReact.statelessComponent "Nav.Link";
  let make
      tag::(tag: string)="a"
      getRef::(getRef: option [ | `String string | `Element ReasonReact.reactElement])=?
      disabled::(disabled: bool)=false
      active::(active: bool)=false
      className::(className: option string)=?
      onClick::(onClick: option (ReactEventRe.Mouse.t => unit))=?
      href::(href: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children => {
    ...component,
    render: fun self => {
      let click event _self =>
        disabled ?
          ReactEventRe.Mouse.preventDefault event :
          (
            switch onClick {
            | None => ()
            | Some cb => cb event
            }
          );
      let classes =
        classNameReduce
          className [cn "nav-link", ocn ("disabled", disabled), ocn ("active", active)];
      ReasonReact.createDomElement
        tag
        props::{
          "className": classes,
          "onClick": self.handle click,
          "href": Js.Null_undefined.from_opt href
        }
        children
    }
  };
};