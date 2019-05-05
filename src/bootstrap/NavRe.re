include Utils;

[@react.component]
   let make =
       (
         ~tabs: bool=false,
         ~pills: bool=false,
         ~vertical: bool=false,
         ~justified: bool=false,
         ~navbar: bool=false,
         ~className: option(string)=?,
         ~children,
       ) => {
     let className =
       [
         navbar ? "navbar-nav" : "nav",
         tabs ? "nav-tabs" : "",
         pills ? "nav-pills" : "",
         justified ? "nav-justified" : "",
         vertical ? "flex-column" : "",
         unwrapStr(i, className),
       ]
       |> String.concat(" ");
     <ul className> children </ul>;
   };


module Item = {
  [@react.component]
  let make =
      (
        ~className: option(string)=? /* cssModule::(cssModule: option (Js.t {..}))=? */,
        ~children,
      ) => {
    let className =
      ["nav-item", unwrapStr(i, className)] |> String.concat(" ");
    <li className> children </li>;
  };
};

module Link = {
  [@react.component]
  let make =
      (
        ~disabled: bool=false,
        ~active: bool=false,
        ~className: option(string)=?,
        ~onClick: option(ReactEvent.Mouse.t => unit)=?,
        ~href: option(string)=?,
        ~children,
      ) => {
    let onClick = event =>
      disabled
        ? ReactEvent.Mouse.preventDefault(event)
        : (
          switch (onClick) {
          | None => ()
          | Some(cb) => cb(event)
          }
        );
    let className =
      [
        "nav-link",
        disabled ? "disabled" : "",
        active ? "active" : "",
        unwrapStr(i, className),
      ]
      |> String.concat(" ");
    <a className onClick ?href> children </a>;
  };
};

/* This could have more option and classes applied! */

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
           "tag": Js.Nullable.fromOption (optionMap unwrapValue tag),
           "className": Js.Nullable.fromOption className,
           "cssModule": Js.Nullable.fromOption cssModule
         }
         children;
   }; */

/* ~getRef:
   option([ | `String(string) | `Element(ReasonReact.reactElement)])=?, */

/* cssModule::(cssModule: option (Js.t {..}))=? */