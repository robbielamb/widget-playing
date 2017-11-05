include Utils;

/* This could have more option and classes applied! */
let component = ReasonReact.statelessComponent("Nav");

let make =
    (
      ~tabs: bool=false,
      ~pills: bool=false,
      ~vertical: bool=false,
      ~justified: bool=false,
      ~navbar: bool=false,
      ~tag: string="ul",
      ~className: option(string)=?,
      /* cssModule::(cssModule: option (Js.t {..}))=? */ children
    ) => {
  ...component,
  render: (_self) => {
    let classes =
      [
        navbar ? "navbar-nav" : "nav",
        tabs ? "nav-tabs" : "",
        pills ? "nav-pills" : "",
        justified ? "nav-justified" : "",
        vertical ? "flex-column" : "",
        unwrapStr(i, className)
      ]
      |> String.concat(" ");
    ReasonReact.createDomElement(tag, ~props={"className": classes}, children)
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
  let component = ReasonReact.statelessComponent("Nav.Item");
  let make =
      (
        ~tag: string="li",
        ~className: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */ children
      ) => {
    ...component,
    render: (_self) => {
      let classes = ["nav-item", unwrapStr(i, className)] |> String.concat(" ");
      ReasonReact.createDomElement(tag, ~props={"className": classes}, children)
    }
  };
};

module Link = {
  let component = ReasonReact.statelessComponent("Nav.Link");
  let make =
      (
        ~tag: string="a",
        ~getRef: option([ | `String(string) | `Element(ReasonReact.reactElement)])=?,
        ~disabled: bool=false,
        ~active: bool=false,
        ~className: option(string)=?,
        ~onClick: option((ReactEventRe.Mouse.t => unit))=?,
        ~href: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */
        children
      ) => {
    ...component,
    render: (self) => {
      let click = (event, _self) =>
        disabled ?
          ReactEventRe.Mouse.preventDefault(event) :
          (
            switch onClick {
            | None => ()
            | Some(cb) => cb(event)
            }
          );
      let classes =
        ["nav-link", disabled ? "disabled" : "", active ? "active" : "", unwrapStr(i, className)]
        |> String.concat(" ");
      ReasonReact.createDomElement(
        tag,
        ~props={
          "className": classes,
          "onClick": self.handle(click),
          "href": Js.Null_undefined.from_opt(href)
        },
        children
      )
    }
  };
};