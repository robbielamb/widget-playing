include Utils;

module Color = {
  type t =
    | Primary
    | Secondary
    | Success
    | Info
    | Warning
    | Danger
    | Dark
    | Light;
  let toString = (color) =>
    switch color {
    | Primary => "primary"
    | Secondary => "secondary"
    | Success => "success"
    | Info => "info"
    | Warning => "warning"
    | Danger => "danger"
    | Dark => "dark"
    | Light => "light"
    };
};

let component = ReasonReact.statelessComponent("Badge");

let make =
    (
      ~color: Color.t=Color.Secondary,
      ~pill: bool=false,
      ~secondary: bool=false,
      ~tag: string="div",
      ~className: option(string)=?,
      ~href: option(string)=?,
      /*  cssModule::(cssModule: option (Js.t {..}))=? */
      children
    ) => {
  ...component,
  render: (_self) => {
    let tag =
      switch href {
      | None => tag
      | Some(_) => tag == "div" ? "a" : tag
      };
    let badgeColor = "badge-" ++ Color.toString(color);
    let classes =
      [
        "badge",
        badgeColor,
        pill ? "badge-pill" : "",
        secondary ? "badge-secondary" : "",
        unwrapStr(i, className)
      ]
      |> String.concat(" ");
    ReasonReact.createDomElement(
      tag,
      ~props={"className": classes, "href": Js.Null_undefined.from_opt(href)},
      children
    )
  }
};
