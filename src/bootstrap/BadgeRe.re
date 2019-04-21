include Utils;

[@react.component]
let make =
    (
      ~color: ColorsRe.Color.t=ColorsRe.Color.Secondary,
      ~pill: bool=false,
      ~secondary: bool=false,
      ~className: option(string)=?,
      ~href: option(string)=?,
      ~children,
    ) => {
  /*  let tag =
      switch (href) {
      | None => tag
      | Some(_) => tag == "div" ? "a" : tag
      }; */
  let badgeColor = "badge-" ++ ColorsRe.Color.toString(color);
  let className =
    ["badge", badgeColor, pill ? "badge-pill" : "", secondary ? "badge-secondary" : "", unwrapStr(i, className)]
    |> String.concat(" ");

  switch (href) {
  | None => <div className> children </div>
  | Some(href) => <a className href> children </a>
  };
};

/*  cssModule::(cssModule: option (Js.t {..}))=? */