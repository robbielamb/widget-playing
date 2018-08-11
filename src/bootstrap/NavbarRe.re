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
      ~fixed: option(Fixed.t)=?,
      ~sticky: option(string)=?,
      ~color: option(ColorsRe.Background.t)=?,
      ~role: option(string)=?,
      ~tag: string="nav",
      ~className: option(string)=?,
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      ~toggleable: bool=false,
      children,
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
        light ? "navbar-light" : "navbar-dark",
        unwrapStr(ColorsRe.Background.toString, color),
        fixedClass(fixed),
        stickyClass(sticky),
        unwrapStr(i, className),
      ]
      |> String.concat(" ");
    ReactDOMRe.createElementVariadic(
      tag,
      ~props={"className": classes, "role": role} |. ReactDOMRe.objToDOMProps,
      children,
    );
  },
};

module Brand = {
  let component = ReasonReact.statelessComponent("Navbar.Brand");
  let make =
      (
        ~tag: string="a",
        ~className: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */
        ~href: string="",
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        ["navbar-brand", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes, "href": href} |. ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
};

module Toggler = {
  let component = ReasonReact.statelessComponent("Navbar.Toggler");
  let make =
      (
        ~tag: string="button",
        ~type_: string="button",
        ~onClick: option(ReactEvent.Mouse.t => unit)=?,
        ~className: option(string)=?,
        _children,
      ) => {
    ...component,
    render: _self => {
      let span = <span className="navbar-toggler-icon" />;
      let classes =
        ["navbar-toggler", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={
          "type": type_,
          "className": classes,
          "onClick": Js.Nullable.fromOption(onClick),
        } |. ReactDOMRe.objToDOMProps,
        [|span|],
      );
    },
  };
};
