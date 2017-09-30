include Utils;

module Color = {
  type t =
    | Primary
    | Secondary
    | Success
    | Info
    | Warning
    | Danger
    | Light
    | Dark
    | White
    | Transparent;
  let toString color =>
    switch color {
    | Primary => "primary"
    | Secondary => "secondary"
    | Success => "success"
    | Info => "info"
    | Warning => "warning"
    | Danger => "danger"
    | Light => "light"
    | Dark => "dark"
    | White => "white"
    | Transparent => "transparent"
    };
};

module Fixed = {
  type t =
    | Top
    | Bottom;
  let toString fixed =>
    switch fixed {
    | Top => "top"
    | Bottom => "bottom"
    };
};

let component = ReasonReact.statelessComponent "NavBar";

let make
    light::(light: bool)=false
    inverse::(inverse: bool)=false
    full::(full: bool)=false
    fixed::(fixed: option Fixed.t)=?
    sticky::(sticky: option string)=?
    color::(color: option Color.t)=?
    role::(role: option string)=?
    tag::(tag: string)="nav"
    className::(className: option string)=?
    /* cssModule::(cssModule: option (Js.t {..}))=? */
    toggleable::(toggleable: bool)=false
    children => {
  ...component,
  render: fun _self => {
    let bgColor (cls: option 'a) =>
      switch cls {
      | None => ocn ("", false)
      | Some x => ocn ("bg-" ^ Color.toString x, true)
      };
    let fixedClass (cls: option 'b) =>
      switch cls {
      | None => ocn ("", false)
      | Some x => ocn ("fixed-" ^ Fixed.toString x, true)
      };
    let stickyClass (cls: option 'c) =>
      switch cls {
      | None => ocn ("", false)
      | Some x => ocn ("sticky-" ^ x, true)
      };
    let classes =
      classNameReduce
        className
        [
          cn "navbar",
          ocn ("navbar-toggleable", toggleable),
          ocn ("navbar-light", light),
          ocn ("navbar-inverse", inverse),
          ocn ("navbar-full", full),
          bgColor color,
          fixedClass fixed,
          stickyClass sticky
        ];
    ReasonReact.createDomElement tag props::{"className": classes, "role": role} children
  }
};

module Brand = {
  let component = ReasonReact.statelessComponent "Navbar.Brand";
  let make
      tag::(tag: string)="a"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      href::(href: string)="#"
      children => {
    ...component,
    render: fun _self => {
      let classes = classNameReduce className [cn "navbar-brand"];
      ReasonReact.createDomElement tag props::{"className": classes, "href": href} children
    }
  };
};

module Toggler = {
  let component = ReasonReact.statelessComponent "Navbar.Toggler";
  let make
      tag::(tag: string)="button"
      _type::(_type: string)="button"
      className::(className: option string)=?
      right::(right: bool)=false
      left::(left: bool)=false
      children => {
    ...component,
    render: fun _self => {
      let classes =
        classNameReduce
          className
          [
            cn "navbar-toggler",
            ocn ("navbar-toggler-right", right),
            ocn ("navbar-toggler-left", left)
          ];
      ReasonReact.createDomElement tag props::{"type": _type, "className": classes} children
    }
  };
};