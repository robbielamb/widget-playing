include Utils;

let component = ReasonReact.statelessComponent("Badge");

let make =
    (
      ~color: Colors.Color.t=Colors.Color.Secondary,
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
    let badgeColor = "badge-" ++ Colors.Color.toString(color);
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