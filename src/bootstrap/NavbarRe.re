include Utils;

module Fixed = {
  type t =
    | Top
    | Bottom;
  let toString = fixed =>
    switch (fixed) {
    | Top => "top"
    | Bottom => "bottom"
    };
};

let component = ReasonReact.statelessComponent("NavBar");

let make =
    (
      ~light: bool=false,
      ~inverse: bool=false,
      ~full: bool=false,
      ~fixed: option(Fixed.t)=?,
      ~sticky: option(string)=?,
      ~color: option(ColorsRe.Background.t)=?,
      ~role: option(string)=?,
      ~tag: string="nav",
      ~className: option(string)=?,
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      ~toggleable: bool=false,
      children
    ) => {
  ...component,
  render: _self => {
    let fixedClass = (cls: option(Fixed.t)) =>
      switch (cls) {
      | None => ""
      | Some(x) => "fixed-" ++ Fixed.toString(x)
      };
    let stickyClass = (cls: option(string)) =>
      switch (cls) {
      | None => ""
      | Some(x) => "sticky-" ++ x
      };
    let classes =
      [
        "navbar",
        toggleable ? "navbar-toggleable" : "",
        light ? "navbar-light" : "",
        inverse ? "navbar-inverse" : "",
        full ? "navbar-full" : "",
        unwrapStr(ColorsRe.Background.toString, color),
        fixedClass(fixed),
        stickyClass(sticky),
        unwrapStr(i, className)
      ]
      |> String.concat(" ");
    ReasonReact.createDomElement(
      tag,
      ~props={"className": classes, "role": role},
      children
    );
  }
};

module Brand = {
  let component = ReasonReact.statelessComponent("Navbar.Brand");
  let make =
      (
        ~tag: string="a",
        ~className: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */
        ~href: string="#",
        children
      ) => {
    ...component,
    render: _self => {
      let classes =
        ["navbar-brand", unwrapStr(i, className)] |> String.concat(" ");
      ReasonReact.createDomElement(
        tag,
        ~props={"className": classes, "href": href},
        children
      );
    }
  };
};

module Toggler = {
  let component = ReasonReact.statelessComponent("Navbar.Toggler");
  let make =
      (
        ~tag: string="button",
        ~_type: string="button",
        ~className: option(string)=?,
        ~right: bool=false,
        ~left: bool=false,
        children
      ) => {
    ...component,
    render: _self => {
      let classes =
        [
          "navbar-toggler",
          right ? "navbar-toggler-right" : "",
          left ? "navbar-toggler-left" : "",
          unwrapStr(i, className)
        ]
        |> String.concat(" ");
      ReasonReact.createDomElement(
        tag,
        ~props={"type": _type, "className": classes},
        children
      );
    }
  };
};
